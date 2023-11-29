#ifndef GAMEGLOBALS_H
#define GAMEGLOBALS_H

class GameGlobals {
private:
    //0 through 5 for sound volume, multiplied by .2 in sound effects code
    static int sound_volume;

public:
    static const int SCREEN_WIDTH = 1920;
    static const int SCREEN_HEIGHT = 1080;
    GameGlobals() { sound_volume = 5; };

    static void setSoundVolume(int newValue);
    static int getSoundVolume();
};

#endif // GAMEGLOBALS_H
