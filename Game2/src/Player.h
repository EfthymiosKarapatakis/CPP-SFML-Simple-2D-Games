#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class Player {
private:
    sf::RectangleShape shape;

    // Player speed
    float movementSpeed;

    int hp;
    int hp_max;
    
    void initVariables();
    void initShape();
public:
    Player(float x = 0.f, float y = 0.f);
    virtual ~Player();

    // Accessors
    const sf::RectangleShape& getShape() const;
    const int& getHp() const;
    const int& getHpMax() const;

    // Functions
    void takeDamage(const int damage);
    void getHealth(const int health);
    void updateInput();
    void updateWindowBoundsCollisions(const sf::RenderTarget* target);

    void update(const sf::RenderTarget* target);
    void render(sf::RenderTarget* target);
};
