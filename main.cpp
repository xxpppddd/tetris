#include "SDL_utils.h"
#include "game.h"
#include <iostream>
using namespace std;

int main(int argc, char* argv[]) {
    srand(time(0));
    game* tetris = new game();
    const char* WINDOW_TITLE = "Tetris";
    if (tetris -> init(WINDOW_TITLE)) {
        while (tetris -> isrunning() and !tetris -> quitGame()) {
            tetris -> setCurrentTime(SDL_GetTicks());
            tetris -> handleEvents();
            tetris -> gameplay();
            
            tetris -> updateRender();
                        
        }
    }
    while (!tetris -> quitGame()) {
        tetris -> gameOver();
    }
    tetris -> clean();
    
    return 0;
}

