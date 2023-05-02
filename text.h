#ifndef text_h
#define text_h
#pragma once
#include<string>
#include <iostream>
#include<SDL2/SDL.h>
#include<SDL2_ttf/SDL_ttf.h>
using namespace std;

class Text
{
private:
    TTF_Font* font;
    string text;
    SDL_Texture* textTexture = NULL;
    SDL_Rect desRect;
    SDL_Color textColor {208, 45, 31, 255};

public:
    void loadText(string filepath, int size);
    void setText(string text, SDL_Renderer* render);
    void renderText(SDL_Renderer* render, int x, int y);
};


#endif /* text_h */
