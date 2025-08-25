#include "Game.h"

int main() {
    // Init random seed
    srand(static_cast<unsigned> (time(0)));

    // Init game object
    Game game;

    // Game loop
    while (game.running()) {
        game.update();
        game.render();
    }

    // End of application
    return 0;
}
