#pragma once 

#include <iostream>
#include <vector>
#include <ctime>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/Window.hpp>

class Game {
private:
    // Variables
    // Window
    sf::RenderWindow* window;
    sf::VideoMode videoMode;
    sf::Event evnt;

    // Mouse Potitions
    sf::Vector2i mousePosWindow;

    // Game logic
    int points;
    float enemySpawnTimer;
    float enemySpawnTimerMax;
    int maxEnemies;

    // Game object
    std::vector<sf::RectangleShape> enemies;
    sf::RectangleShape enemy;

    // Private Functions 
    void initVariables();
    void initWindow();
    void initEnemies();

public:
    // Constractor
    Game();
    // Destructor
    virtual ~Game();
    
    // Accessors
    const bool running() const;

    // Function
    void spawnEnemy();
    void pollEvents();
    void updateMousePositions();
    void updateEnemies();
    void renderEnemies();
    void update();
    void render();
};
