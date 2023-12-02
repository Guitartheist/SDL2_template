#ifndef ENTITY_H
#define ENTITY_H

#include "../utility/SoundEffect.h"
#include "../utility/StringTexture.h"
#include "../gamestate/GameGlobals.h"
#include <SDL.h>

class Entity {
private:
protected:
    float x;
    float y;
    int width;
    int height;
    float xVelocity;
    float yVelocity;
    SoundEffect *soundEffect;
    string ID;
    int teamID;
    SDL_Color mainColor;
    SDL_Color detailColor;
    SDL_Color accentColor;
    StringTexture* label;
    SDL_Renderer* gRenderer;
    bool dead = false;
public:
    virtual void move();
    virtual void render() {return;};
    virtual void render(int x, int y) {return;};
    virtual void die() {dead = true;};
    virtual void scoreKill(Entity *otherEntity) {return;};
    virtual bool isDead() {return dead;};
    virtual bool didCollide(Entity *otherEntity);

    float getX() {return x;};
    float getY() {return y;};
    void setX(float sx) { x = sx; };
    void setY(float sy) { y = sy; };

    int getWidth() {return width;};
    int getHeight() {return height;};

    float getXVelocity() {return xVelocity;};
    float getYVelocity() {return yVelocity;};
    void setXVelocity(float setX) { xVelocity = setX; };
    void setYVelocity(float setY) { yVelocity = setY; };

    string getID() { return ID; };
    void setID(string sID) { ID = sID; };

    int getTeamID() {return teamID;};
    void setTeamID(int s) {teamID=s;};

    SDL_Color getMainColor() { return mainColor; };
    SDL_Color getDetailColor() { return detailColor; };
    SDL_Color getAccentColor() { return accentColor; };
    void setMainColor(SDL_Color setC) { mainColor.a = setC.a; mainColor.b = setC.b; mainColor.g = setC.g; mainColor.r = setC.r; };
    void setDetailColor(SDL_Color setC) { detailColor.a = setC.a; detailColor.b = setC.b; detailColor.g = setC.g; detailColor.r = setC.r; };
    void setAccentColor(SDL_Color setC) { accentColor.a = setC.a; accentColor.b = setC.b; accentColor.g = setC.g; accentColor.r = setC.r; };

    ~Entity();
};

#endif // ENTITY_H
