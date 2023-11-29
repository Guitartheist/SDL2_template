#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <SDL.h>

#include "../movers/ExampleDude.h"

class Controller {
private:
protected:
    bool up = false;
    bool down = false;
    bool left = false;
    bool right = false;
    bool action = false;
    bool actionAcknowledged = false;
    SDL_GameController *controller = nullptr;
    ExampleDude* dude = nullptr;
public:
    Controller(SDL_GameController *setController);
    SDL_GameController *getController() {return controller;};

    void handleEvent(SDL_Event* event);

    void move();

    bool getUp() {return up;};
    bool getDown() {return down;};
    bool getLeft() {return left;};
    bool getRight() {return right;};
    bool getAction() {return action;};
    bool getActionAcknowledged() {return actionAcknowledged;};
    ExampleDude* getDude() {return dude;};

    void setUp(bool s) {up=s;};
    void setDown(bool s) {down=s;};
    void setLeft(bool s) {left=s;};
    void setRight(bool s) {right=s;};
    void setAction(bool s) {action=s;};
    void setActionAcknowledged(bool s) {actionAcknowledged=s;};
    void setDude(ExampleDude* s) {dude=s;};
};

#endif // CONTROLLER_H
