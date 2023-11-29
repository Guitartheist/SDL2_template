#include "Controller.h"

Controller::Controller(SDL_GameController* setController)
{
    controller = setController;
}

void Controller::handleEvent(SDL_Event* event)
{
    if (dude==nullptr) {
        return;
    }

    switch (event->type) {
    case SDL_CONTROLLERBUTTONDOWN:
        action = true;
        actionAcknowledged = false;
        break;
    case SDL_CONTROLLERBUTTONUP:
        action = false;
        break;
    case SDL_CONTROLLERAXISMOTION:
        //xbox RT = axis 5
        //xbox LT = axis 4
        //xbox left stick up/down = axis 1
        //xbox left stick left/right = axis 0
        //xbox right stick up/down = axis 3
        //xbox right stick left/right = axis 2
        switch (event->caxis.axis) {
            case 0:
                if (event->caxis.value>10000) {
                   right = true;
                   left = false;
                }
                else if (event->caxis.value<-10000) {
                   right = false;
                   left = true;
                }
                else {
                    right = false;
                    left = false;
                }
                break;
            case 1:
                if (event->caxis.value>10000) {
                    down = true;
                    up = false;
                }
                else if (event->caxis.value<-10000) {
                    up = true;
                    down = false;
                }
                else {
                    up = false;
                    down = false;
                }
                break;
        }
        break;
    }

}

void Controller::move()
{
    if (dude==nullptr) {
        return;
    }
    if (up) {
        dude->setY( dude->getY() - 1 );
    }
    else if (down) {
        dude->setY( dude->getY() + 1 );
    }
    if (left) {
        dude->setX( dude->getX() - 1 );
    }
    else if (right) {
        dude->setX( dude->getX() + 1 );
    }
}

