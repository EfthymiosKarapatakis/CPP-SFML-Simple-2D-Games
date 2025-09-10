#include "Game.h"

int main() {
    // Init random seed
    srand(static_cast<unsigned> (time(0)));

    // Init game object
    Game game;

    // Game loop
    while (game.running() /*&& !game.getEndGame()*/) { // with this when hp<=0 the game will close with no end game text
        game.update();
        game.render();
    }

    // End of application
    return 0;
}
