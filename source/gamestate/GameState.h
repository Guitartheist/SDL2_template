#ifndef GAMESTATE_H
#define GAMESTATE_H

#define MAX_CONTROLLERS 10
#define AI_CONTROLLED -1000
#define KEYBOARD_CONTROLLED -2000

#include "GameGlobals.h"
#include "Controller.h"
#include <SDL.h>
#include <map>
#include <deque>
#include "../utility/SoundEffect.h"
#include "../utility/StringTexture.h"

#include "../movers/ExampleDude.h"

using namespace std;

class GameState {
    private:
        Uint32 currentTicks;

        const int FRAMES_PER_SECOND = 60;
        const int SCREEN_WIDTH = 1920;
        const int SCREEN_HEIGHT = 1080;
        Uint32 frameDelay;
        Uint32 nextFrame;
        SDL_Window *gWindow;
        SDL_Renderer *gRenderer;
        SDL_Color orange = {0xFF,0x66,0x00,0xFF};
        SDL_Color yellow = {0xFF,0xFF,0x00,0xFF};
        SDL_Color red = {0xFF,0x00,0x00,0xFF};
        SDL_Color green = {0x00,0xFF,0x00,0xFF};
        SDL_Color blue = {0x64,0x95,0xED,0xFF};
        SDL_Color white = {0xFF,0xFF,0xFF,0xFF};
        SDL_Color transparentWhite = {0xFF,0xFF,0xFF, 100};
        SDL_Color pink = {0xFF,0x69,0xB4,0xFF};
        SDL_Event event;

        SoundEffect sound_effect;

        int framesPlayed = 0;

        bool quit = false;
        bool pause = false;

        bool escMenu = false;

        int playerCount = 0;

        StringTexture* volumeToggleString;
        StringTexture* fullscreenString;
        StringTexture* quitString;
        StringTexture* exitString;
        StringTexture* resumeString;

        bool fullScreen = true;

        //temp controller pointer for opening and closing controllers
        SDL_GameController *controller;
        Controller *gameController;
        map<Sint32, Controller*> controllers;

        //what actions are selected by the keyboard player
        Controller *keyBoardController;
        //has the keyboard player join the game
        bool keyBoardActive;

        //The objects of the game - players, AI, the level, etc
        deque<ExampleDude*> dudes;

    public:
        GameState(SDL_Window* window, SDL_Renderer* renderer);
        void handleGameplayInput();
        void move();
        void render();
        void playLoop();

        ExampleDude* nextAvailableDude();

        ~GameState();
};

#endif // GAMESTATE_H
