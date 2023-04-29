
#include "game.h"
#include "SDL_utils.h"
/*
 0 1 2 3
 4 5 6 7
 */

const int game::shapes[7][4] =
{
    0, 1, 5, 6, //Z
    2, 6, 5, 4, //L
    2, 1, 5, 4, //S
    0, 1, 2, 3, //I
    1, 4, 5, 6, //T
    0, 4, 5, 6, //J
    1, 2, 5, 6, //O
};

bool game::init(const char* WINDOW_TITLE) {
    initSDL(window, renderer, SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
    Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 4096);
        Mix_Music* music = NULL;
        music = Mix_LoadMUS("/Users/phucd/Desktop/lập trình nâng cao/tetris/music/aespa_tetris.mp3");
        Mix_PlayMusic(music, 127);
    background = loadTexture("/Users/phucd/Desktop/lập trình nâng cao/tetris/tetris_image/tetris_background.png", renderer);
    blocks_img = loadTexture("/Users/phucd/Desktop/lập trình nâng cao/tetris/tetris_image/blocks1.png", renderer);
    over = loadTexture("/Users/phucd/Desktop/lập trình nâng cao/tetris/tetris_image/over.png", renderer);
    nextTetromino();
    gameIsOver = false;
    quit = false;
    return true;
}

void game::nextTetromino() {
    color = 1 + rand() % 7;
    shape = color - 1;
    for (int i = 0; i < 4; i++) {
        blocks[i].x = shapes[shape][i] % 4;
        blocks[i].y = int (shapes[shape][i] / 4);
    }
}

void game::handleEvents() {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
            quit = true;
        }
        else if (e.type == SDL_KEYDOWN) {
            // Handle key presses
            switch (e.key.keysym.sym) {
                case SDLK_LEFT:
                    // Move tetromino left
                    step = -1;
                    break;
                case SDLK_RIGHT:
                    // Move tetromino right
                    step = 1;
                    break;
                case SDLK_DOWN:
                    // Move tetromino down
                    delay = 0;
                    break;
                case SDLK_SPACE:
                    // Rotate tetromino
                    rotate = true;
                    break;
                case SDLK_ESCAPE:
                    // Quit game
                    quit = true;
                    break;
                default: break;
            }
        }
    }
}
void game::setRectPosition(SDL_Rect &rect, int x, int y, int w, int h) {
    rect = {x, y, w, h};
}

void game::moveRectPosition(SDL_Rect& rect, int x, int y) {
    rect.x += x;
    rect.y += y;
}

bool game::isvalid() {
    for (int i = 0; i < 4; i++) {
        if (blocks[i].x < 0 or blocks[i].x >= cols or blocks[i].y >= rows or blocks[i].y < 0) return false;
        else if (board[blocks[i].y][blocks[i].x]) return false;
    }
    return true;
}

void game::gameplay() {
    
    //backup
    for (int i = 0; i < 4; i++) {
        temp_blocks[i] = blocks[i];
    }
    //move
    if (step) {
        for (int i = 0; i < 4; i++) {
            blocks[i].x += step;
        }
        if (!isvalid()) {
            for (int i = 0; i < 4; i++) {
                blocks[i] = temp_blocks[i];
            }
        }
    }
    //rotate
    if (rotate) {
        point p = blocks[2];
        for (int i = 0; i < 4; i++) {
            int x = blocks[i].y - p.y;
            int y = blocks[i].x - p.x;
            blocks[i].x = p.x - x;
            blocks[i].y = p.y + y;
        }
        if (!isvalid() or shape == 6) {
            for (int i = 0; i < 4; i++) {
                blocks[i] = temp_blocks[i];
            }
        }
    }
    //tick
    if (currentTime - startTime > delay) {
        for (int i = 0; i < 4; i++) {
            temp_blocks[i] = blocks[i];
        }
        for (int i = 0; i < 4; i++) {
            blocks[i].y++;
        }
        if (!isvalid()) {
            for (int i = 0; i < 4; i++) {
                board[temp_blocks[i].y][temp_blocks[i].x] = color;
            }
            nextTetromino();
        }
        startTime = currentTime;
    }
    
    //check rows
    int k = rows - 1;
    for (int i = k; i > 0; i--) {
        int count = 0;
        for (int j = 0; j < cols; j++) {
            if (board[i][j]) count++;
            board[k][j] = board [i][j];
        }
        if (count < cols) {
            k--;
        }
        if (count == cols) {
            score += 100;
        }
    }
    
    //game over
    for (int i = 0; i < cols; i++) {
        if (board[0][i] != 0) {
            gameIsOver = true;
            break;
        }
    }

    
    step = 0;
    rotate = false;
    delay = 600;
    
}
void game::updateRender() {
    SDL_RenderCopy(renderer, background, NULL, NULL);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (board[i][j]) {
                setRectPosition(srcR, board[i][j] * block_size);
                setRectPosition(desR, j * block_size, i* block_size);
                moveRectPosition(desR, 70, 50);
                SDL_RenderCopy(renderer, blocks_img, &srcR, &desR);
            }
        }
    }
    for (int i = 0; i < 4; i++) {
        setRectPosition(srcR, color * block_size);
        setRectPosition(desR, blocks[i].x * block_size, blocks[i].y * block_size);
        moveRectPosition(desR, 70, 50);
        SDL_RenderCopy(renderer, blocks_img, &srcR, &desR);
    }
    
    SDL_RenderPresent(renderer);
}



void game::gameOver() {
    over = loadTexture("/Users/phucd/Desktop/lập trình nâng cao/tetris/tetris_image/over.png", renderer);
    SDL_RenderCopy(renderer, over, NULL, NULL);
    SDL_RenderPresent(renderer);
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
            quit = true;
        }
    }
    
}



void game::clean() {
    SDL_DestroyTexture(blocks_img);
    SDL_DestroyTexture(background);
    SDL_DestroyRenderer(renderer);
    IMG_Quit();
    SDL_Quit();
    TTF_Quit();

}

