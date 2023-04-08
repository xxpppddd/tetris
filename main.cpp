#include "SDL_utils.h"
#include "tetromino.h"
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
    
    waitUntilKeyPressed();

    quitSDL(window, renderer);
    return 0;

}
