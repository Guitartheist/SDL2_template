#include "StringTexture.h"

#include "../gamestate/GameGlobals.h"

StringTexture::StringTexture(SDL_Renderer* renderer, string fontPath, SDL_Color* setColor, int fontSize, string newText)
{
    gRenderer = renderer;
    setFont( fontPath.c_str() , fontSize );
    color = setColor;
    setText(newText);
}

void StringTexture::setFont(string fontPath, int fontSize)
{
    if (font!=NULL && font!=nullptr) {
        TTF_CloseFont(font);
    }
    font = TTF_OpenFont( fontPath.c_str() , fontSize );
    if (font==nullptr) {
    }
    else {
    }
}

void StringTexture::setText(string newText)
{
    text = newText;
    if (texture!=NULL) {
        SDL_DestroyTexture(texture);
    }
    surface = TTF_RenderText_Solid( font, text.c_str(), *color);
    texture = SDL_CreateTextureFromSurface( gRenderer, surface );
    width = surface->w;
    height = surface->h;
    SDL_FreeSurface(surface);
}

void StringTexture::setColor(SDL_Color* setTo)
{
    color = setTo;
    if (texture!=NULL) {
        SDL_DestroyTexture(texture);
    }
    surface = TTF_RenderText_Solid( font, text.c_str(), *color);
    texture = SDL_CreateTextureFromSurface( gRenderer, surface );
    width = surface->w;
    height = surface->h;
    SDL_FreeSurface(surface);
}

SDL_Color* StringTexture::getColor()
{
    return color;
}


void StringTexture::render(int x, int y)
{
    SDL_Rect renderQuad{ x, y, width, height};
    SDL_RenderCopy(gRenderer, texture, NULL, &renderQuad);
}

void StringTexture::renderCenterOfTextAt(int x, int y)
{
    int xCenter = x - width / 2;
    int yCenter = y - height / 2;
    SDL_Rect renderQuad{ xCenter, yCenter, width, height};
    SDL_RenderCopy(gRenderer, texture, NULL, &renderQuad);
}

void StringTexture::renderCenterOfScreen()
{
    int xCenter = GameGlobals::SCREEN_WIDTH / 2 -  width / 2;
    int yCenter = GameGlobals::SCREEN_HEIGHT / 2 - height / 2;
    SDL_Rect renderQuad{ xCenter, yCenter, width, height};
    SDL_RenderCopy(gRenderer, texture, NULL, &renderQuad);
}

StringTexture::~StringTexture()
{
    if (font!=nullptr) {
        TTF_CloseFont(font);
    }
    if (texture!=nullptr) {
        SDL_DestroyTexture(texture);
    }
}

