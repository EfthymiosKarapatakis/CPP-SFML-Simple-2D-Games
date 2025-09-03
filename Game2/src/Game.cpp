#include "Game.h"
#include "Player.h"

void Game::initVariables() {
    this->endGame = false;
    this->spawnTimerMax = 10.f;
    this->spawnTimer = this->spawnTimerMax;
    this->maxSwagBalls = 10;
    this->points = 0;
}

void Game::initWindow() {
    this->videomode = sf::VideoMode(800, 600);
    this->window = new sf::RenderWindow(this->videomode, "Game 2", sf::Style::Close | sf::Style::Titlebar);
    this->window->setFramerateLimit(60);
}

void Game::initFont() {
    if (!this->font.loadFromFile("fonts/MozillaHeadline-VariableFont_wdth,wght.ttf")) {
        std::cout << " ! ERRORR::GAME::INITFONTS::COULD NOT LOAD MozillaHeadline" << "\n";
    }
}

void Game::initText() {
    // Gui text init
    this->guiText.setFont(this->font);
    this->guiText.setFillColor(sf::Color::White);
    this->guiText.setCharacterSize(24);
    this->guiText.setString("test");
}

// Constructor
Game::Game() {
    this->initVariables();
    this->initWindow();
    this->initFont();
    this->initText();
}

// Destructor
Game::~Game() {
    delete this->window;
}


// Functions
const bool Game::running() const {
    return this->window->isOpen();
}

void Game::pollEvents() {
    while(this->window->pollEvent(this->evnt)) {
        switch (this->evnt.type) {
            case sf::Event::Closed:
                this->window->close();
                break;
            case sf::Event::KeyPressed:
            if (this->evnt.key.code == sf::Keyboard::Escape)
                this->window->close();
            break;
        }
    }
}

void Game::spawnSwagBalls() {
    // Timer
    if (this->spawnTimer < this->spawnTimerMax) {
        this->spawnTimer += 1.f;
    } else {
        if (this->SwagBalls.size() < this->maxSwagBalls) {
            this->SwagBalls.push_back(Swagball(*this->window));

            this->spawnTimer = 0.f;
        }
    }

}

void Game::updateCollisions() {
    //Check the collition
    for (size_t i = 0; i<this->SwagBalls.size(); i++) {
        if(this->player.getShape().getGlobalBounds().intersects(this->SwagBalls[i].getShape().getGlobalBounds())) {
            this->SwagBalls.erase(this->SwagBalls.begin() + i);
            this->points++;
        }
    }
}

void Game::updateGui() {
    std::stringstream ss;

    ss << "Points: " << this->points;
    this->guiText.setString(ss.str());
}

void Game::renderGui(sf::RenderTarget* target) {
    target->draw(this->guiText);
}

void Game::update()
{
    this->pollEvents();

    this->spawnSwagBalls();
    this->player.update(this->window);
    this->updateCollisions();
    this->updateGui();
}

void Game::render() {
    this->window->clear();

    this->player.render(this->window);

    // Render stuff
    for (auto i : this->SwagBalls) {
        i.render(*this->window);
    }

    // Render gui
    this->renderGui(this->window);

    this->window->display();
}


