#include "Game.h"
#include "Player.h"

void Game::initVariables() {
    this->endGame = false;
    this->spawnTimerMax = 10.f;
    this->spawnTimer = this->spawnTimerMax;
    this->maxSwagBalls = 10;
}

void Game::initWindow() {
    this->videomode = sf::VideoMode(800, 600);
    this->window = new sf::RenderWindow(this->videomode, "Game 2", sf::Style::Close | sf::Style::Titlebar);
    this->window->setFramerateLimit(60);
}

// Constructor
Game::Game() {
    this->initVariables();
    this->initWindow();

}

// Destructor
Game::~Game() {
    delete this->window;
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
            this->SwagBalls.push_back(Swagball(*this->window));

            this->spawnTimer = 0.f;
        }
    }

}

void Game::update()
{
    this->pollEvents();

    this->spawnSwagBalls();
    this->player.update(this->window);
}

void Game::render() {
    this->window->clear();

    // Render stuff
    for (auto i : this->SwagBalls) {
        i.render(*this->window);
    }

    this->player.render(this->window);

    this->window->display();
}


