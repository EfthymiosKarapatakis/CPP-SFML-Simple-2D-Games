#include "Game.h"

// Private functions
void Game::initVariables() {
    this->window = nullptr;

    // Game Logic
    this->endGame = false;
    this->points = 0;
    this->enemySpawnTimerMax = 10.f;
    this->enemySpawnTimer = this->enemySpawnTimerMax;
    this->maxEnemies = 5;   // Enemy count
    this->mouseHeld = false;
    this->health = 100;
}

void Game::initWindow() {
    this->videoMode.height = 600;
    this->videoMode.width = 800;

    this->window = new sf::RenderWindow(this->videoMode, "Game 1", sf::Style::Titlebar | sf::Style::Close);

    this->window->setFramerateLimit(120);
}

void Game::initEnemies() {
    this->enemy.setPosition(10.f, 10.f);
    this->enemy.setSize(sf::Vector2f(100.f, 100.f));
    this->enemy.setScale(sf::Vector2f(0.5f, 0.5f));
    this->enemy.setFillColor(sf::Color::Cyan);
    // this->enemy.setOutlineColor(sf::Color::Green);
    // this->enemy.setOutlineThickness(1.f);
}

// Constructors
Game::Game() {
    this->initVariables();
    this->initWindow();
    this->initEnemies();
}

// Destructors
Game::~Game() {
    delete this->window;
}

// Accessors
const bool Game::running() const{
    return this->window->isOpen();
}

const bool Game::getEndGame() const {
    return this->endGame;
}

// Function
void Game::spawnEnemy() {
    /*
    Spawns enemies and set the color and positions
    - Sets a random color
    - Sets a random position
    - Adds enemies to the vector
    - moves the enemies down
    */

    this->enemy.setPosition(static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->enemy.getSize().x)), 0.f);

    /*
    ! Add multiple enemies
    - Green: 100px, 1 point, speed 0.8 and 60% chance to spawn
    - blue: 75px, 3 points, speed 1.75 and 30% chance to spawn
    - red: 50px, 5 points, speed 3 and 10% chance to spawn
    */
    float chance = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);

    if (chance < 0.6f) {  // Green 60%
        this->enemy.setFillColor(sf::Color::Green);
        this->enemy.setSize(sf::Vector2f(100.f, 100.f));
    } else if (chance < 0.9f) {  // Blue 30%
        this->enemy.setFillColor(sf::Color::Blue);
        this->enemy.setSize(sf::Vector2f(70.f, 70.f));
    } else {
        this->enemy.setFillColor(sf::Color::Red);
        this->enemy.setSize(sf::Vector2f(55.f, 55.f));
    }
    this->enemies.push_back(this->enemy);
}

void Game::pollEvents() {
    // Event pull
    while (this->window->pollEvent(this->evnt)) {
    switch (this->evnt.type) {
        case sf::Event::Closed:
            this->window->close();
            break;
        case sf::Event::KeyPressed:
            if(this->evnt.key.code == sf::Keyboard::Escape)
                this->window->close();
            break;
        }
    }
}

void Game::updateMousePositions() {
    this->mousePosWindow = sf::Mouse::getPosition(*this->window);
    this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}

void Game::updateEnemies() {
    // Updates the timer for enemy spawning
    if (this->enemies.size() < this->maxEnemies) {
        if (this->enemySpawnTimer >= this->enemySpawnTimerMax) {
            // Spawn the enemy and reset the timer
            this->spawnEnemy();
            this->enemySpawnTimer = 0.f;
        } else {
            this->enemySpawnTimer += 1.f;
        }
    } else {
        this->enemySpawnTimer += 1.f;
    }


    for (int i=0; i < this->enemies.size(); i++) {
        // Moves enemies down
        this->enemies[i].move(0.f, 1.f);
        if (enemies[i].getFillColor() == sf::Color::Green) {
            this->enemies[i].move(0.f, .8f);
        } else if (enemies[i].getFillColor() == sf::Color::Blue) {
            this->enemies[i].move(0.f, 1.75f);
        }else {
            this->enemies[i].move(0.f, 3.f);
        }
        // If the enemy is past the bottom of the screen
        if(this->enemies[i].getPosition().y > this->window->getSize().y) {
            this->enemies.erase(this->enemies.begin() + i);
            this->health--;
            std::cout << "Health: " << this->health << "\n";
        }
    }

    // Deletes an enemy if mouse key is pressed and then check the location
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        

        if (this->mouseHeld == false) {
            this->mouseHeld = true;
            bool deleted = false;
        
            for (size_t i=0; i < this->enemies.size() && deleted == false; i++) {
                if (this->enemies[i].getGlobalBounds().contains(mousePosView)) {
                    deleted = true;
                    this->enemies.erase(this->enemies.begin() + i);

                    // Gain points
                    if (enemies[i].getFillColor() == sf::Color::Green) {
                        points += 1;
                    } else if (enemies[i].getFillColor() == sf::Color::Blue) {
                        points += 3;
                    }else {
                        points += 5;
                    }

                    std::cout << "Points" << this->points << "\n";
                }
            }
        }
    } else {
        this->mouseHeld = false;
    }
}


void Game::update()
{
    this->pollEvents();

    if (this->endGame == false) {
        this->updateMousePositions();
        this->updateEnemies();
    }

    if (this->health <= 0) {
        this->endGame = true;
    }



    // Update mouce position 
    
    // Relative to the screen
    //std::cout << "Mouse pos: " << sf::Mouse::getPosition().x << ", " << sf::Mouse::getPosition().y << "\n";
    
    // Relative to the window
    //std::cout << "Mouse pos: " << sf::Mouse::getPosition(*this->window).x << ", " << sf::Mouse::getPosition(*this->window).y << "\n";
}

void Game::renderEnemies() {
    for (auto &e : this->enemies) {
        this->window->draw(e);
    }
}

void Game::render() {
    // clear screen before you draw
    this->window->clear();

    // Draw Ubjects
    this->renderEnemies();

    //Display Objects
    this->window->display();
}
