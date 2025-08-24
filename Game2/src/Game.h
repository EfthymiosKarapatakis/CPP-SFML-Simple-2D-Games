#pragma once

#include <iostream>
#include <ctime>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class Game {
private:
    sf::VideoMode videomode;
    sf::RenderWindow* window;
    bool endGame;

    void initVariables();
    void initWindow();

public:
    // Constuctor and destructor
    Game();
    ~Game();

    // Accessors

    // Modifiers

    // Functions
    void update();
    void render();
};
