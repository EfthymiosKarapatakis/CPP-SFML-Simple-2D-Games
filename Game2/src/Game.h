#pragma once

#include <iostream>
#include <ctime>
#include <vector>
#include <sstream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include "Player.h"
#include "SwagBall.h"

class Game {
private:
    sf::VideoMode videomode;
    sf::RenderWindow* window;
    bool endGame;
    sf::Event evnt;

    Player player;

    int points;

    sf::Font font;
    sf::Text guiText;

    std::vector<Swagball> SwagBalls;
    float spawnTimerMax;
    float spawnTimer;
    int maxSwagBalls;

    void initVariables();
    void initWindow();
    void initFont();
    void initText();

public:
    // Constuctor and destructor
    Game();
    ~Game();

    // Accessors

    // Modifiers

    // Functions
    const bool running() const;
    void pollEvents();

    void spawnSwagBalls();
    void updateCollisions();
    void updateGui();
    
    void renderGui(sf::RenderTarget* target);

    void update();
    void render();
};
