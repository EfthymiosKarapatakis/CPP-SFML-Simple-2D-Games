#include "Player.h"

void Player::initVariables() {
    this->movementSpeed = 10.f;
}

void Player::initShape() {
    this->shape.setFillColor(sf::Color::Green);
    this->shape.setSize(sf::Vector2f(50.f, 50.f));
}

Player::Player(float x, float y) { 
    // Set player potition
    this->shape.setPosition(x, y);

    this->initVariables();
    this->initShape();
}

Player::~Player() {

}

// Keyboard input
void Player::updateInput() {
    // Left or Right (A or D)
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        this->shape.move(-this->movementSpeed, 0.f);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        this->shape.move(this->movementSpeed, 0.f);
    }
    // Up or Down (W or S)
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        this->shape.move(0.f, -this->movementSpeed);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        this->shape.move(0.f, this->movementSpeed);
    }
}

// Window bounds collision
void Player::updateWindowBoundsCollisions(const sf::RenderTarget *target) {
    
    // Left
    if (this->shape.getGlobalBounds().left <= 0) {
        this->shape.setPosition(0.f, this->shape.getGlobalBounds().top);
    }
    
    // Right
    if ((this->shape.getGlobalBounds().left + this->shape.getGlobalBounds().width) >= target->getSize().x) {
        this->shape.setPosition(target->getSize().x - this->shape.getGlobalBounds().width, this->shape.getGlobalBounds().top);
    }

    // Top
    if (this->shape.getGlobalBounds().top <= 0) {
        this->shape.setPosition(this->shape.getGlobalBounds().left ,0.f);
    } 
    
    // Bottom
    if ((this->shape.getGlobalBounds().top + this->shape.getGlobalBounds().height) >= target->getSize().y) {
        this->shape.setPosition(this->shape.getGlobalBounds().left, target->getSize().y - this->shape.getGlobalBounds().height);
    }
}

void Player::update(const sf::RenderTarget* target) {
    // Keyboard input
    this->updateInput();
    
    // Window bounds collision
    this->updateWindowBoundsCollisions(target);

    
}

void Player::render(sf::RenderTarget * target) {
    target->draw(this->shape);
}
