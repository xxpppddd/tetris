//
//  text.cpp
//  tetris
//
//  Created by phuc dinh on 4/29/23.
//

#include "text.h"

void Text::loadText(string filepath, int size)
{
    font = TTF_OpenFont(filepath.c_str(), size);
    if (font == NULL) {
        std::cout << "lỗi";
    }
}

void Text::setText(string text, SDL_Renderer* render)
{
    if(text != this->text && text != "")
    {
        if(textTexture != NULL)
            SDL_DestroyTexture(textTexture);
        this->text = text;

        SDL_Surface* surface = TTF_RenderText_Blended(font, text.c_str(), textColor);
        textTexture = SDL_CreateTextureFromSurface(render, surface);
        SDL_FreeSurface(surface);
        SDL_QueryTexture(textTexture, NULL, NULL, &desRect.w, &desRect.h);
    }

}

void Text::renderText(SDL_Renderer* render, int x, int y)
{
    desRect.x = x;
    desRect.y = y;
    SDL_RenderCopy(render, textTexture, NULL, &desRect);

}


