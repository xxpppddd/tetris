
#ifndef TETROMINO_H
#define TETROMINO_H


#pragma once
#include <SDL2/SDL.h>
using namespace std;

const int blockSize = 30;

class Tetromino {
public:
    Tetromino(SDL_Rect* blocks, SDL_Color color);
    void render(SDL_Renderer* renderer, int x, int y);

private:
    SDL_Rect* m_blocks;
    SDL_Color m_color;
};

extern SDL_Rect I_Blocks[4];
extern SDL_Rect J_Blocks[4];
extern SDL_Rect L_Blocks[4];
extern SDL_Rect O_Blocks[4];
extern SDL_Rect S_Blocks[4];
extern SDL_Rect T_Blocks[4];
extern SDL_Rect Z_Blocks[4];


extern Tetromino I_Shape;
extern Tetromino J_Shape;
extern Tetromino L_Shape;
extern Tetromino O_Shape;
extern Tetromino S_Shape;
extern Tetromino T_Shape;
extern Tetromino Z_Shape;


#endif /* tetromino_h */
