#include "Game.h"

// Private functions
void Game::initVariables() {
    this->window = nullptr;
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
    this->initEnemies();

    // Update mouce position 
    
    // Relative to the screen
    //std::cout << "Mouse pos: " << sf::Mouse::getPosition().x << ", " << sf::Mouse::getPosition().y << "\n";
    
    // Relative to the window
    std::cout << "Mouse pos: " << sf::Mouse::getPosition(*this->window).x << ", " << sf::Mouse::getPosition(*this->window).y << "\n";

} 

void Game::render() {
    this->window->clear();

    // Draw Ubjects
    this->window->draw(this->enemy);

    //Display Objects
    this->window->display();
}
