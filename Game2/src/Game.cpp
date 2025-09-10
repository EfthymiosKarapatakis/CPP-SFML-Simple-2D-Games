#include "Game.h"
#include "Player.h"

void Game::initVariables() {
    this->endGame = false;
    this->spawnTimerMax = 10.f;
    this->spawnTimer = this->spawnTimerMax;
    this->maxSwagBalls = 10;
    this->points = 0;
}

void Game::initWindow() {
    this->videomode = sf::VideoMode(800, 600);
    this->window = new sf::RenderWindow(this->videomode, "Game 2", sf::Style::Close | sf::Style::Titlebar);
    this->window->setFramerateLimit(60);
}

void Game::initFont() {
    if (!this->font.loadFromFile("fonts/MozillaHeadline-VariableFont_wdth,wght.ttf")) {
        std::cout << " ! ERRORR::GAME::INITFONTS::COULD NOT LOAD MozillaHeadline" << "\n";
    }
}

void Game::initText() {
    // Gui text init
    this->guiText.setFont(this->font);
    this->guiText.setFillColor(sf::Color::White);
    this->guiText.setCharacterSize(24);
    this->guiText.setString("Gui text");

    // End game text init
    this->endGameText.setFont(this->font);
    this->endGameText.setFillColor(sf::Color::Red);
    this->endGameText.setCharacterSize(60);
    this->endGameText.setString("End game text");
    this->endGameText.setPosition(sf::Vector2f(20, 300));
    this->endGameText.setString("YOU ARE DEAD,\nEXIT THE GAME!");
}

// Constructor
Game::Game() {
    this->initVariables();
    this->initWindow();
    this->initFont();
    this->initText();
}

// Destructor
Game::~Game() {
    delete this->window;
}

const bool &Game::getEndGame() const {
    return this->endGame;
}

// Functions
const bool Game::running() const {
    return this->window->isOpen();
}

void Game::pollEvents() {
    while(this->window->pollEvent(this->evnt)) {
        switch (this->evnt.type) {
            case sf::Event::Closed:
                this->window->close();
                break;
            case sf::Event::KeyPressed:
            if (this->evnt.key.code == sf::Keyboard::Escape)
                this->window->close();
            break;
        }
    }
}

void Game::spawnSwagBalls() {
    // Timer
    if (this->spawnTimer < this->spawnTimerMax) {
        this->spawnTimer += 1.f;
    } else {
        if (this->SwagBalls.size() < this->maxSwagBalls) {
            this->SwagBalls.push_back(Swagball(*this->window, this->randomizeBallType()));

            this->spawnTimer = 0.f;
        }
    }

}

const int Game::randomizeBallType() const {
    int type = SwagBallTypes::DEFAULT;

    /*
    ? 60% chance for default balls (points)
    ? 20% chance for damaging balls
    ? 20% chance of healing balls
    */
    int randValue = rand() % 100 + 1;
    if (randValue > 60 && randValue < 80) {
        type = SwagBallTypes::DAMAGING;
    } else if (randValue >= 80 && randValue <= 100) {
        type = SwagBallTypes::HEALING;
    }

    return type;
}

void Game::updateCollisions() {
    //Check the collition
    for (size_t i = 0; i<this->SwagBalls.size(); i++) {
        if(this->player.getShape().getGlobalBounds().intersects(this->SwagBalls[i].getShape().getGlobalBounds())) {
            // 
            switch (this->SwagBalls[i].getType())
            {
            case SwagBallTypes::DEFAULT:
                // Add points
                this->points++;
                break;
            case SwagBallTypes::DAMAGING:
                this->player.takeDamage(10);
                break;
            case SwagBallTypes::HEALING:
                this->player.getHealth(10);
                break;
            default:
                break;
            }

            // Remove the ball
            this->SwagBalls.erase(this->SwagBalls.begin() + i);
        }
    }
}

void Game::updatePlayer() {
    this->player.update(this->window);
    if (this->player.getHp() <= 0) {
        this->endGame = true;
    }
}

void Game::updateGui() {
    std::stringstream ss;

    ss << " - Points: " << this->points << "\n - Health: " << this->player.getHp() << "/" << this->player.getHpMax();
    this->guiText.setString(ss.str());
}

void Game::renderGui(sf::RenderTarget* target) {
    target->draw(this->guiText);
}

void Game::update()
{
    this->pollEvents();

    if (this->endGame == false) {
        this->spawnSwagBalls();
        this->updatePlayer();
        this->updateCollisions();
        this->updateGui();
    }
}

void Game::render() {
    this->window->clear();

    this->player.render(this->window);

    // Render stuff
    for (auto i : this->SwagBalls) {
        i.render(*this->window);
    }

    // Render gui
    this->renderGui(this->window);

    // Render end game
    if (this->endGame == true) {
        this->window->draw(this->endGameText);
    }

    this->window->display();
}


