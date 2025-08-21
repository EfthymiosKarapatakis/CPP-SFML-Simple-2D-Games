#pragma once 

#include <iostream>
#include <vector>
#include <ctime>
#include <sstream>

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

    // Fonts
    sf::Font font;

    // Text
    sf::Text uiText;

    // Mouse Potitions
    sf::Vector2i mousePosWindow;
    sf::Vector2f mousePosView;

    // Game logic
    bool endGame;
    unsigned points;
    float enemySpawnTimer;
    float enemySpawnTimerMax;
    int maxEnemies;
    bool mouseHeld;
    int health;

    // Game object
    std::vector<sf::RectangleShape> enemies;
    sf::RectangleShape enemy;

    // Private Functions 
    void initVariables();
    void initWindow();
    void initFonts();
    void initText();
    void initEnemies();

public:
    // Constractor
    Game();
    // Destructor
    virtual ~Game();
    
    // Accessors
    const bool running() const;
    const bool getEndGame() const;

    // Function
    void spawnEnemy();
    void pollEvents();
    void updateMousePositions();
    void updateEnemies();
    void renderEnemies(sf::RenderTarget& target);
    void update();
    void renderText(sf::RenderTarget& target);
    void updateText();
    void render();
};
