#ifndef EXAMPLEDUDE_H
#define EXAMPLEDUDE_H

#include "Entity.h"

class ExampleDude: public Entity {
private:
protected:
    bool cross = false;
    bool humanControlled = false;
public:
    int HEIGHT = 54;
    int WIDTH = 19;
    ExampleDude(SDL_Renderer* setRenderer, float setX, float setY, SDL_Color setMain, SDL_Color setDetail, SDL_Color setAccent, bool setCross);
    void render();
    void render(int x, int y);

    bool getHumanControlled() {return humanControlled;};
    void setHumanControlled(bool s) {humanControlled = s;};

    ~ExampleDude();
};

#endif // EXAMPLEDUDE_H
