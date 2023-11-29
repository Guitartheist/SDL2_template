#include "Entity.h"

void Entity::move()
{
    x += xVelocity;
    y += yVelocity;
    while (x < 0) {
        x += GameGlobals::SCREEN_WIDTH;
    }
    while (x > GameGlobals::SCREEN_WIDTH) {
        x -= GameGlobals::SCREEN_WIDTH;
    }
    while (y < 0) {
        y += GameGlobals::SCREEN_HEIGHT;
    }
    while (y > GameGlobals::SCREEN_HEIGHT) {
        y -= GameGlobals::SCREEN_HEIGHT;
    }
}

bool Entity::didCollide(Entity* otherEntity)
{
    if (otherEntity == this) {
        return false;
    }
    if (dead) {
        return false;
    }

    float otherXVelocity = otherEntity->getXVelocity();
    float otherYVelocity = otherEntity->getYVelocity();

    float minx1 = x;
    float miny1 = y;
    float maxx1 = x + width;
    float maxy1 = y + height;

    float minx2 = otherEntity->getX();
    float miny2 = otherEntity->getY();
    float maxx2 = minx2 + otherEntity->getWidth();
    float maxy2 = miny2 + otherEntity->getHeight();

    //if actual positions intersect, return true
    if (maxx1 >= minx2 && minx1 <= maxx2 && maxy1 >= miny2 && miny1 <= maxy2) {
        return true;
    }

    //check to see if positions in between frames might have collided, return false if no possibility
    //if moving left, move bounding box edge right to account for previous positions
    if (xVelocity < 0) {
        maxx1 -= xVelocity;
    }
    //if moving right, move bounding box edge left to account for previous positions
    else {
        minx1 -= xVelocity;
    }
    //if moving left, move bounding box edge right to account for previous positions
    if (otherXVelocity < 0) {
        maxx2 -= otherXVelocity;
    }
    //if moving right, move bounding box edge left to account for previous positions
    else {
        minx2 -= otherXVelocity;
    }
    //if moving up, move bounding box edge down to account for previous positions
    if (yVelocity < 0) {
        maxy1 -= yVelocity;
    }
    //if moving down, move bounding box edge up to account for previous positions
    else {
        miny1 -= yVelocity;
    }
    //if moving up, move bounding box edge down to account for previous positions
    if (otherYVelocity < 0) {
        maxy2 -= otherYVelocity;
    }
    //if moving down, move bounding box edge up to account for previous positions
    else {
        miny2 -= otherYVelocity;
    }

    //if intermediate collision is possible, binary search intermediate positions, return true if any of them intersect
    //For now, if an intermediate collision is possible, we just return true. If necessary we can write binary search for more precision.
    if (maxx1 >= minx2 && minx1 <= maxx2 && maxy1 >= miny2 && miny1 <= maxy2) {
        return true;
    }
    return false;
}

Entity::~Entity()
{
    if (label != nullptr) {
        delete label;
    }
}

