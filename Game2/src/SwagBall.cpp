#include "SwagBall.h"

void Swagball::initShape(const sf::RenderWindow& window) {
    this->shape.setRadius(static_cast<float>(rand() % 10 + 10));    // random size

    // Set color
    sf::Color color;
    switch (this->type)
    {
    case DEFAULT:
        color = sf::Color::Blue;
        break;
    case DAMAGING:
        color = sf::Color::Red;
        break;
    case HEALING:
        color = sf::Color::Green;
        break;
    default:
        break;
    }


    
    this->shape.setFillColor(color);
    this->shape.setPosition(
        sf::Vector2f(
            static_cast<float>(rand() % window.getSize().x - this->shape.getGlobalBounds().width),
            static_cast<float>(rand() % window.getSize().y - this->shape.getGlobalBounds().height)
        )
    ); 
}

Swagball::Swagball(const sf::RenderWindow& window, int type) : type(type) {
    this->initShape(window);
}

Swagball::~Swagball() {
    
}

// Functions
const sf::CircleShape Swagball::getShape() const {
    return this->shape;
}

const int Swagball::getType() const {
    return this->type;
}

void Swagball::update() {

}

void Swagball::render(sf::RenderTarget & target) {
    target.draw(this->shape);
}
