
#ifndef game_h
#define game_h

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_mixer/SDL_mixer.h>
#include <string>
#include "text.h"
#include "SDL_utils.h"

class game {
public:
    game() {
        
    }
    ~game() {
        
    }
    void setCurrentTime(Uint32 t) {
        currentTime = t;
    }
    bool isrunning() {
        return !gameIsOver;
    }
    bool quitGame() {
        return (quit);
    }
    bool paused() {
        return pause;
    }
    bool restartGame() {
        return restart;
    }
    bool isvalid();
    
    bool init(const char* title);
    void menu();
    void nextTetromino();
    void handleEvents();
    void setRectPosition(SDL_Rect& rect, int x = 0, int y = 0, int w = block_size, int h = block_size);
    void moveRectPosition(SDL_Rect& rect, int x, int y);
    void gameplay();
    void updateRender();
    void gameOver();
    void reset();
    void clean();
private:
    enum {SCREEN_WIDTH = 700, SCREEN_HEIGHT = 700};
    enum {block_size = 30};
    enum {rows = 20, cols = 10};
    
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    SDL_Texture* menuTexture = NULL;
    SDL_Texture* background = NULL;
    SDL_Texture* over = NULL;
    SDL_Texture* blocks_img = NULL;
    SDL_Rect srcR = {0, 0, block_size, block_size}, desR = {0, 0, block_size, block_size};
    
    bool quit = true;
    bool pause = false;
    bool gameIsOver = true;
    int board[rows][cols] = {0};
    static const int shapes[7][4];
    struct point {
        int x;
        int y;
    } blocks[4], temp_blocks[4], next_blocks[4];
    int current_shape;
    int shape;
    int color = 1;
    int next_color = 1;
    int step = 0;
    int score = 0;
    bool rotate = false;
    unsigned int delay = 600;
    int temp_delay;
    int showMenu = 0;
    string score_text;
    Uint32 #ifndef game_h
#define game_h

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_mixer/SDL_mixer.h>
#include <string>
#include "text.h"
#include "SDL_utils.h"

class game {
public:
    game() {
        
    }
    ~game() {
        
    }
    void setCurrentTime(Uint32 t) {
        currentTime = t;
    }
    bool isrunning() {
        return !gameIsOver;
    }
    bool quitGame() {
        return (quit);
    }
    bool paused() {
        return pause;
    }
    bool restartGame() {
        return restart;
    }
    bool isvalid();
    
    bool init(const char* title);
    void menu();
    void nextTetromino();
    void handleEvents();
    void setRectPosition(SDL_Rect& rect, int x = 0, int y = 0, int w = block_size, int h = block_size);
    void moveRectPosition(SDL_Rect& rect, int x, int y);
    void gameplay();
    void updateRender();
    void gameOver();
    void reset();
    void clean();
private:
    enum {SCREEN_WIDTH = 700, SCREEN_HEIGHT = 700};
    enum {block_size = 30};
    enum {rows = 20, cols = 10};
    
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    SDL_Texture* menuTexture = NULL;
    SDL_Texture* background = NULL;
    SDL_Texture* over = NULL;
    SDL_Texture* blocks_img = NULL;
    SDL_Rect srcR = {0, 0, block_size, block_size}, desR = {0, 0, block_size, block_size};
    
    bool quit = true;
    bool pause = false;
    bool gameIsOver = true;
    int board[rows][cols] = {0};
    static const int shapes[7][4];
    struct point {
        int x;
        int y;
    } blocks[4], temp_blocks[4], next_blocks[4];
    int current_shape;
    int shape;
    int color = 1;
    int next_color = 1;
    int step = 0;
    int score = 0;
    bool rotate = false;
    unsigned int delay;
    int showMenu = 0;
    string score_text;
    Uint32 startTime = 0, currentTime = 0;
    Text scoreText;
    bool restart = true;
};


#endif
 = 0, currentTime = 0;
    Text scoreText;
    bool restart = true;
};



#endif

