#include "game.h"

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

void game::menu()
{
    SDL_Texture* menuTexture = IMG_LoadTexture(renderer, "menu.png");
    SDL_Event e;
    bool menuLoop = true;
    while(menuLoop)
    {
        while(SDL_PollEvent(&e) != 0)
        {
            if(e.type == SDL_QUIT)
            {
                menuLoop = false;
                restart = false;
                quit = true;
                break;
            }
            else if(e.type == SDL_KEYDOWN)
            {
                switch(e.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        menuLoop = false;
                        restart = false;
                        quit = true;
                        break;
                    default:
                        menuLoop = false;
                        break;
                }
            }
        }

        SDL_RenderCopy(renderer, menuTexture, NULL, NULL);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(menuTexture);
}

bool game::init(const char* WINDOW_TITLE) {
    initSDL(window, renderer, SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
    return true;
}




void game::nextTetromino() {
    color = next_color;
    next_color = 1 + rand() % 7;
    current_shape = shape;
    shape = next_color - 1;
    for (int i = 0; i < 4; i++) {
        blocks[i].x = next_blocks[i].x;
        blocks[i].y = next_blocks[i].y;
    }
    for (int i = 0; i < 4; i++) {
        next_blocks[i].x = shapes[shape][i] % 4;
        next_blocks[i].y = int (shapes[shape][i] / 4);
    }
}


void game::handleEvents() {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
            restart = false;
            quit = true;
        }
        else if (e.type == SDL_KEYDOWN) {
            if (!pause) {
                switch (e.key.keysym.sym) {
                    case SDLK_LEFT:
                        step = -1;
                        break;
                    case SDLK_RIGHT:
                        step = 1;
                        break;
                    case SDLK_DOWN:
                        delay = 0;
                        break;
                    case SDLK_SPACE:
                        rotate = true;
                        break;
                    case SDLK_ESCAPE:
                        restart = false;
                        quit = true;
                        break;
                    case SDLK_p:
                        pause = !pause;
                        
                        break;
                    default: break;
                }
            }
            else {
                if (e.key.keysym.sym == SDLK_p) {
                    pause = !pause;
                }
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
        if (!isvalid() or current_shape == 6) {
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
    
    //check hàng
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
        score_text = to_string(score);
        scoreText.setText(score_text, renderer);
    }
    
    //difficulty
    if (score < 1000) {
        temp_delay = 500;
    }
    else if (score >= 1000 and score < 2000) {
        temp_delay = 400;
    }
    else if (score >= 2000 and score < 3500) {
        temp_delay = 300;
    }
    else if (score >= 3500 and score < 5000){
        temp_delay = 200;
    }
    else {
        temp_delay = 100;
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
    delay = temp_delay;
    
}
void game::updateRender() {
    if (showMenu == 0) {
        menu();
        showMenu++;
    }
    if (!quit) {
        SDL_RenderCopy(renderer, background, NULL, NULL);
        if (score == 0) scoreText.renderText(renderer, 505, 170);
        else if (score >= 100 and score < 1000) scoreText.renderText(renderer, 485, 170);
        else if (score >= 1000 and score < 10000) scoreText.renderText(renderer, 478, 170);
        else scoreText.renderText(renderer, 470, 170);
        
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
            setRectPosition(srcR, next_color * block_size);
            setRectPosition(desR, next_blocks[i].x * block_size, next_blocks[i].y * block_size);
            if (shape == 6 or shape == 3) moveRectPosition(desR, 460, 530);
            else moveRectPosition(desR, 475, 530);
            SDL_RenderCopy(renderer, blocks_img, &srcR, &desR);
        }
        for (int i = 0; i < 4; i++) {
            setRectPosition(srcR, color * block_size);
            setRectPosition(desR, blocks[i].x * block_size, blocks[i].y * block_size);
            moveRectPosition(desR, 70, 50);
            SDL_RenderCopy(renderer, blocks_img, &srcR, &desR);
        }
    }
    SDL_RenderPresent(renderer);
}



void game::gameOver() {
    Mix_PauseMusic();
    over = loadTexture("over.png", renderer);
    SDL_RenderCopy(renderer, over, NULL, NULL);
    scoreText.setText("Your score: " + score_text, renderer);
    if (score == 0) scoreText.renderText(renderer, 250, 412);
    else if (score >= 100 and score < 1000) scoreText.renderText(renderer, 228, 412);
    else if (score >= 1000 and score < 10000) scoreText.renderText(renderer, 219, 412);
    else scoreText.renderText(renderer, 211, 412);
    SDL_RenderPresent(renderer);
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
            quit = true;
            restart = false;
        }
        else if(e.type == SDL_KEYDOWN)
        {
            switch(e.key.keysym.sym)
            {
                case SDLK_ESCAPE:
                    quit = true;
                    restart = false;
                    break;
                default:
                    restart = true;
                    break;
            }
        }
    }
    
    
}

void game::reset() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            board[i][j] = 0;
        }
    }
    Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 4096);
    Mix_Music* music = NULL;
    music = Mix_LoadMUS("aespa_tetris.mp3");
    Mix_PlayMusic(music, -1);
    
    background = loadTexture("tetris_background.png", renderer);
    blocks_img = loadTexture("blocks.png", renderer);
    over = loadTexture("over.png", renderer);
    if(TTF_Init() != 0)
        cout << TTF_GetError();
    scoreText.loadText("NeueHaasDisplayMedium.ttf", 36);
    scoreText.setText("0", renderer);
    next_color = 1 + rand() % 7;
    shape = next_color - 1;
    for (int i = 0; i < 4; i++) {
        next_blocks[i].x = shapes[shape][i] % 4;
        next_blocks[i].y = int (shapes[shape][i] / 4);
    }
    nextTetromino();
    score = 0;
    gameIsOver = false;
    pause = false;
    quit = false;
    restart = false;
}
void game::clean() {
    SDL_DestroyTexture(blocks_img);
    SDL_DestroyTexture(background);
    SDL_DestroyTexture(over);
    SDL_DestroyTexture(menuTexture);
    SDL_DestroyRenderer(renderer);
    IMG_Quit();
    SDL_Quit();
    TTF_Quit();

}



