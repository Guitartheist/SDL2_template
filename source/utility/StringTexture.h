#ifndef STRINGTEXTURE_H
#define STRINGTEXTURE_H

#include <SDL_ttf.h>
#include <string>
#include <iostream>

using namespace std;

class StringTexture{
    private:
        TTF_Font* font = nullptr;
        SDL_Surface* surface = nullptr;
        SDL_Texture* texture = nullptr;
        SDL_Color* color;
        SDL_Renderer* gRenderer;
        string text;
        int width;
        int height;
    protected:
    public:
        StringTexture(SDL_Renderer* renderer, string fontPath, SDL_Color* setColorTo, int fontSize, string newText);

        void setFont(string fontPath, int fontSize);
        TTF_Font* getFont() {return font;};

        void setText(string text);
        void render(int x, int y);
        void renderCenterOfTextAt(int x, int y);
        void renderCenterOfScreen();

        void setColor(SDL_Color* setTo);
        SDL_Color* getColor();
        string getText() {return text;};

        ~StringTexture();
};

#endif // STRINGTEXTURE_H
