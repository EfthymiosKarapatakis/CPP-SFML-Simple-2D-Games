#pragma once

#include <iostream>
#include <ctime>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include "Player.h"

class Game {
private:
    sf::VideoMode videomode;
    sf::RenderWindow* window;
    bool endGame;
    sf::Event evnt;

    Player player;

    void initVariables();
    void initWindow();

public:
    // Constuctor and destructor
    Game();
    ~Game();

    // Accessors

    // Modifiers

    // Functions
    const bool running() const;
    void pollEvents();
    void update();
    void render();
};
