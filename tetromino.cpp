#include "tetromino.h"

Tetromino::Tetromino(SDL_Rect* blocks, SDL_Color color) {
    m_blocks = blocks;
    m_color = color;
}

void Tetromino::render(SDL_Renderer* renderer, int x, int y) {
    SDL_Rect blockRect;
    blockRect.w = blockSize;
    blockRect.h = blockSize;

    for (int i = 0; i < 4; i++) {
        // Set the position of the current block
        blockRect.x = x + m_blocks[i].x ;
        blockRect.y = y + m_blocks[i].y ;

        // Set the color of the current block
        SDL_SetRenderDrawColor(renderer, m_color.r, m_color.g, m_color.b, m_color.a);

        // Render the current block
        SDL_RenderFillRect(renderer, &blockRect);
    }
}
SDL_Rect I_Blocks[4] = {
    {0, 0, 30, 30},
    {0, 30, 30, 30},
    {0, 60, 30, 30},
    {0, 90, 30, 30}
};

SDL_Rect J_Blocks[4] = {
    {0, 0, 30, 30},
    {30, 0, 30, 30},
    {60, 0, 30, 30},
    {0, 30, 30, 30}
};

SDL_Rect L_Blocks[4] = {
    {0, 0, 30, 30},
    {30, 0, 30, 30},
    {60, 0, 30, 30},
    {60, 30, 30, 30}
};

SDL_Rect O_Blocks[4] = {
    {0, 0, 30, 30},
    {30, 0, 30, 30},
    {0, 30, 30, 30},
    {30, 30, 30, 30}
};

SDL_Rect S_Blocks[4] = {
    {0, 0, 30, 30},
    {30, 0, 30, 30},
    {60, 30, 30, 30},
    {30, 30, 30, 30}
};

SDL_Rect T_Blocks[4] = {
    {0, 0, 30, 30},
    {30, 0, 30, 30},
    {60, 0, 30, 30},
    {30, 30, 30, 30}
};

SDL_Rect Z_Blocks[4] = {
    {0, 30, 30, 30},
    {30, 0, 30, 30},
    {60, 0, 30, 30},
    {30, 30, 30, 30}
};

Tetromino I_Shape(I_Blocks, { 0, 255, 255, 255 });
Tetromino J_Shape(J_Blocks, { 0, 0, 255, 255 });
Tetromino L_Shape(L_Blocks, { 255, 127, 0, 255 });
Tetromino O_Shape(O_Blocks, { 255, 255, 0, 255 });
Tetromino S_Shape(S_Blocks, { 0, 255, 0, 255 });
Tetromino T_Shape(T_Blocks, { 128, 0, 128, 255 });
Tetromino Z_Shape(Z_Blocks, { 255, 0, 0, 255 });

