#include "Game.h"

// Private functions
void Game::initVariables() {
    this->window = nullptr;

    // Game Logic
    this->points = 0;
    this->enemySpawnTimerMax = 1000.f;
    this->enemySpawnTimer = this->enemySpawnTimerMax;
    this->maxEnemies = 5;
}

void Game::initWindow() {
    this->videoMode.height = 600;
    this->videoMode.width = 800;

    this->window = new sf::RenderWindow(this->videoMode, "Game 1", sf::Style::Titlebar | sf::Style::Close);

    //this->window->setFramerateLimit(60);
}

void Game::initEnemies() {
    this->enemy.setPosition(10.f, 10.f);
    this->enemy.setSize(sf::Vector2f(100.f, 100.f));
    this->enemy.setScale(sf::Vector2f(0.5f, 0.5f));
    this->enemy.setFillColor(sf::Color::Cyan);
    this->enemy.setOutlineColor(sf::Color::Green);
    this->enemy.setOutlineThickness(1.f);
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

// Function
void Game::spawnEnemy() {
    /*
    Spawns enemies and set the color and positions
    - Sets a random color
    - Sets a random position
    - Adds enemies to the vector
    - moves the enemies down
    */

    this->enemy.setPosition(
        static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->enemy.getSize().x)), 0.f);

    this->enemy.setFillColor(sf::Color::Green);

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

    // Remove enmies at the edge of the screen (TODO)
    
    // Moves enemies
    for (auto &e : this->enemies) {
        e.move(0.f, 1.f);   // Move the enemies down
    }
}

void Game::update()
{
    this->pollEvents();

    this->updateMousePositions();

    this->updateEnemies();


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
