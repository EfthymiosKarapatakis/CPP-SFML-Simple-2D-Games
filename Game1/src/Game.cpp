#include "Game.h"

// Private functions
void Game::initVariables() {
    this->window = nullptr;
}

void Game::initWindow() {
    this->videoMode.height = 600;
    this->videoMode.width = 800;

    this->window = new sf::RenderWindow(this->videoMode, "Game 1", sf::Style::Titlebar | sf::Style::Close);
}


// Constructors
Game::Game() {
    this->initVariables();
    this->initWindow();
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

void  Game::update() {
    this->pollEvents();
}

void Game::render() {
    this->window->clear(sf::Color(255, 0, 0));

    // Draw Game

    this->window->display();
}
