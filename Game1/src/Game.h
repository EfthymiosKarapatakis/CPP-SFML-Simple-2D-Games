#pragma once 

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

    // Private Functions
    void initVariables();
    void initWindow();

public:
    // Constractor
    Game();
    // Destructor
    virtual ~Game();
    
    // Accessors
    const bool running() const;

    // Function
    void pollEvents();
    void update();
    void render();
};
