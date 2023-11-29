#include "GameGlobals.h"

int GameGlobals::sound_volume;


void GameGlobals::setSoundVolume(int newValue)
{
    sound_volume = newValue;
}

int GameGlobals::getSoundVolume()
{
    return sound_volume;
}
