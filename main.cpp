#include "SDL_utils.h"
#include "tetromino.h"
#include "game.h"
#include <SDL2_mixer/SDL_mixer.h>
#include <iostream>


int main(int argc, char* argv[])
{
    const int SCREEN_WIDTH = 700;
    const int SCREEN_HEIGHT = 700;
    const string WINDOW_TITLE = "Tetris";
    SDL_Window* window;
    SDL_Renderer* renderer;
    initSDL(window, renderer, SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
    //drawing code
    SDL_Texture* background = loadTexture("/Users/phucd/Desktop/lập trình nâng cao/tetris/tetris_image/tetris_background.png", renderer);
    SDL_RenderCopy(renderer, background, NULL, NULL);
    SDL_RenderPresent(renderer);

    Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 4096);
    Mix_Music* music = NULL;
    music = Mix_LoadMUS("/Users/phucd/Desktop/lập trình nâng cao/tetris/music/aespa_tetris.mp3");
    Mix_PlayMusic(music, 127);
    Tetromino tetromino = randomTetromino();
    tetromino.render(renderer, 70, 50);
    

    bool quit = false;
    while (!quit) {

        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            switch (e.type) {
                case SDL_QUIT:
                    quit = true;
                    break;
                case SDL_KEYDOWN:
                    switch (e.key.keysym.sym) {
                        case SDLK_LEFT:
                            // Move tetromino left
                            tetromino.move_left();
                            
                            break;
                        case SDLK_RIGHT:
                            // Move tetromino right
                            tetromino.move_right();
                            break;
                        case SDLK_DOWN:
                            // Move tetromino down
                            tetromino.move_down();
                            break;
                        case SDLK_SPACE:
                            // Rotate tetromino
                            tetromino.rotate();
                            break;
                    }
                    break;
            }
        }

        // Clear screen
 

        // Draw game board
        // Draw tetromino
        

        // Update screen

        // Wait for some time
        SDL_Delay(10);
    }

    
    

    quitSDL(window, renderer);
    return 0;

}

