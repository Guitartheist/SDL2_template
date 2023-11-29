#include "ExampleDude.h"

ExampleDude::ExampleDude(SDL_Renderer* setRenderer, float setX, float setY, SDL_Color setMain, SDL_Color setDetail, SDL_Color setAccent, bool setCross)
{
    gRenderer = setRenderer;

    x = setX;
    y = setY;

    mainColor.r = setMain.r;
    mainColor.g = setMain.g;
    mainColor.b = setMain.b;
    mainColor.a = setMain.a;

    detailColor.r = setDetail.r;
    detailColor.g = setDetail.g;
    detailColor.b = setDetail.b;
    detailColor.a = setDetail.a;

    accentColor.r = setAccent.r;
    accentColor.g = setAccent.g;
    accentColor.b = setAccent.b;
    accentColor.a = setAccent.a;

    cross = setCross;
}

void ExampleDude::render()
{
    render(x, y);
    if (x + WIDTH > GameGlobals::SCREEN_WIDTH && y + HEIGHT < GameGlobals::SCREEN_HEIGHT) {
        render (x - GameGlobals::SCREEN_WIDTH, y);
    }
    if (x + WIDTH > GameGlobals::SCREEN_WIDTH && y + HEIGHT > GameGlobals::SCREEN_HEIGHT) {
        render (x - GameGlobals::SCREEN_WIDTH, y - GameGlobals::SCREEN_HEIGHT);
    }
    if (y + HEIGHT > GameGlobals::SCREEN_HEIGHT) {
        render (x, y - GameGlobals::SCREEN_HEIGHT);
    }
}

//head is 9 pixels
//torso is 18 pixels wide and 45 pixels tall
void ExampleDude::render(int x, int y)
{
    SDL_Rect head = { x+6, y, 7, 9 };
    SDL_Rect torso = { x, y+9 , 19, 45 };

    SDL_SetRenderDrawColor( gRenderer, mainColor.r, mainColor.g, mainColor.b, mainColor.a );
    SDL_RenderFillRect( gRenderer, &head );
    SDL_RenderFillRect( gRenderer, &torso );

    SDL_SetRenderDrawColor( gRenderer, detailColor.r, detailColor.g, detailColor.b, detailColor.a );
    SDL_RenderDrawRect( gRenderer, &head );
    SDL_RenderDrawRect( gRenderer, &torso );

    SDL_SetRenderDrawColor( gRenderer, accentColor.r, accentColor.g, accentColor.b, accentColor.a );

    if (cross) {
        SDL_RenderDrawLine( gRenderer, x+1, y+30 , x+17, y+30 );
        SDL_RenderDrawLine( gRenderer, x+1, y+31 , x+17, y+31 );
        SDL_RenderDrawLine( gRenderer, x+1, y+32 , x+17, y+32 );

        SDL_RenderDrawLine( gRenderer, x+8, y+10 , x+8, y+52 );
        SDL_RenderDrawLine( gRenderer, x+9, y+10 , x+9, y+52 );
        SDL_RenderDrawLine( gRenderer, x+10, y+10 , x+10, y+52 );
    }

    else {
        SDL_RenderDrawLine( gRenderer, x+1, y+10 , x+15, y+52 );
        SDL_RenderDrawLine( gRenderer, x+1, y+52 , x+15, y+10 );

        SDL_RenderDrawLine( gRenderer, x+2, y+10 , x+16, y+52 );
        SDL_RenderDrawLine( gRenderer, x+2, y+52 , x+16, y+10 );

        SDL_RenderDrawLine( gRenderer, x+3, y+10 , x+17, y+52 );
        SDL_RenderDrawLine( gRenderer, x+3, y+52 , x+17, y+10 );
    }
}

ExampleDude::~ExampleDude()
{

}
