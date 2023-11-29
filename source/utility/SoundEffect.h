#ifndef SOUNDEFFECT_H
#define SOUNDEFFECT_H

#include <SDL.h>

struct SoundEffect {
    float frequency;
    uint64_t samples_played;
    bool rising_tone;
    uint64_t length;
};

#endif // SOUNDEFFECT_H
