#include "GameState.h"

#include "../utility/SoundEffect.h"
#include "../utility/StringTexture.h"

#include <iostream>
#include <map>
#include <algorithm>
#include <vector>

#include <cstdint>
#include <cmath>

using namespace std;

void audio_callback(void* userdata, uint8_t* stream, int len)
{
    SoundEffect* sound_effect = (SoundEffect*)userdata;
    float* fstream = (float*)(stream);
    float volume = 0.5;
    volume *= (0.2 * GameGlobals::getSoundVolume());

    if (sound_effect->samples_played >= sound_effect->length) {
        for(int sid = 0; sid < (len / 8); ++sid)
        {
            fstream[2 * sid + 0] = 0; /* L */
            fstream[2 * sid + 1] = 0; /* R */
        }
        return;
    }

    if (sound_effect->rising_tone) {
        sound_effect->frequency += ((sound_effect->frequency * 2 ) / (float) sound_effect->length) * (len/8);
    }
    else {
        sound_effect->frequency -= ((sound_effect->frequency / 2 ) / (float) sound_effect->length) * (len/8);
    }

    //PLAY THE CURRENT NOTE
    for(int sid = 0; sid < (len / 8); ++sid)
    {
        double time = (sound_effect->samples_played + sid) / 44100.0;
        fstream[2 * sid + 0] = volume * sin(sound_effect->frequency * 2.0 * M_PI * time); /* L */
        fstream[2 * sid + 1] = volume * sin(sound_effect->frequency * 2.0 * M_PI * time); /* R */
    }

    sound_effect->samples_played += (len / 8);
}

GameState::GameState(SDL_Window* window, SDL_Renderer *renderer)
{
    gWindow = window;

    string fontPath = "./font.ttf";
    framesPlayed = 0;
    gRenderer = renderer;
    frameDelay = 1000/FRAMES_PER_SECOND;

    keyBoardController = new Controller(nullptr);

    //SDL Audio
        sound_effect.samples_played = 0;
        sound_effect.frequency = 275.0;
        sound_effect.rising_tone = false;
        sound_effect.length = 11025;

        SDL_AudioSpec audio_spec_want, audio_spec;
        SDL_memset(&audio_spec_want, 0, sizeof(audio_spec_want));

        audio_spec_want.freq     = 44100;
        audio_spec_want.format   = AUDIO_F32;
        audio_spec_want.channels = 2;
        audio_spec_want.samples  = 512;
        audio_spec_want.callback = audio_callback;
        audio_spec_want.userdata = (void*)&sound_effect;

        SDL_AudioDeviceID audio_device_id = SDL_OpenAudioDevice(
            NULL, 0,
            &audio_spec_want, &audio_spec,
            SDL_AUDIO_ALLOW_FORMAT_CHANGE
        );

        SDL_PauseAudioDevice(audio_device_id, 0);

    //ESC menu stuff

    GameGlobals::setSoundVolume(2);
    string volumeString = "Volume_(0-5):_";
        volumeString.append(std::to_string(GameGlobals::getSoundVolume()));
        volumeString.append("_");
    volumeToggleString = new StringTexture(gRenderer, fontPath, &white, 30, volumeString);

    string FSString("(F)ullscreen:_");
    if (fullScreen) {
        FSString.append("On_");
    }
    else {
        FSString.append("Off_");
    }
    fullscreenString = new StringTexture(gRenderer, fontPath, &white, 30, FSString);

    string QString = "(Q)uit round and return to join screen";
    quitString = new StringTexture(gRenderer, fontPath, &white, 30, QString);
    string XString = "E(x)it game and return to desktop";
    exitString = new StringTexture(gRenderer, fontPath, &white, 30, XString);
    string RString = "(ESC)_To resume the round";
    resumeString = new StringTexture(gRenderer, fontPath, &white, 30, RString);

    dudes.push_back( new ExampleDude(gRenderer, 100, 900, orange, white, yellow, true) );
    dudes.push_back( new ExampleDude(gRenderer, 200, 900, orange, white, yellow, false) );
    dudes.push_back( new ExampleDude(gRenderer, 300, 900, orange, white, green, true) );
    dudes.push_back( new ExampleDude(gRenderer, 400, 900, orange, white, green, false) );
    dudes.push_back( new ExampleDude(gRenderer, 500, 900, orange, white, white, true) );
    dudes.push_back( new ExampleDude(gRenderer, 600, 900, blue, transparentWhite, white, false) );
    dudes.push_back( new ExampleDude(gRenderer, 700, 900, blue, transparentWhite, green, true) );
    dudes.push_back( new ExampleDude(gRenderer, 800, 900, blue, transparentWhite, green, false) );
    dudes.push_back( new ExampleDude(gRenderer, 900, 900, blue, transparentWhite, red, true) );
    dudes.push_back( new ExampleDude(gRenderer, 1000, 900, blue, transparentWhite, red, false) );
}

void GameState::move() {
    //Controller actions
    keyBoardController->move();
    for (auto it = controllers.begin(); it != controllers.end(); ++it) {
        if (it->second != nullptr) {
            it->second->move();
        }
    }
    //Move dudes
    for (long long unsigned int  i=0; i<dudes.size(); i++) {
        if (dudes[i] != nullptr) {
            dudes[i]->move();
        }
    }
}

void GameState::render() {
    //Clear screen
    SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0xFF );
    SDL_RenderClear( gRenderer );

    //Draw dudes
    for (long long unsigned int  i=0; i<dudes.size(); i++) {
        if (dudes[i] != nullptr)
            dudes[i]->render();
    }

    if (escMenu) {
        SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
        int left = SCREEN_WIDTH/2 - SCREEN_WIDTH/4;
        int top = SCREEN_HEIGHT/2 - SCREEN_HEIGHT/4;
        int centerX = SCREEN_WIDTH/2;
        int centerY = SCREEN_HEIGHT/2;
        SDL_Rect escMenuBackground = {left, top, SCREEN_WIDTH/2, SCREEN_HEIGHT/2};
        SDL_RenderFillRect(gRenderer, &escMenuBackground);

        //ESC menu stuff
        string volumeString = "Volume_(0-5):_";
        volumeString.append(std::to_string(GameGlobals::getSoundVolume()));
        volumeString.append("_");
        volumeToggleString->setText(volumeString);
        volumeToggleString->renderCenterOfTextAt(centerX, centerY - 40);

        string FSString("(F)ullscreen:_");
        if (fullScreen) {
            FSString.append("On_");
        }
        else {
            FSString.append("Off_");
        }
            fullscreenString->setText(FSString);

        fullscreenString->renderCenterOfTextAt(centerX, centerY );
        quitString->renderCenterOfTextAt(centerX, centerY + 40);
        exitString->renderCenterOfTextAt(centerX, centerY + 80);
        resumeString->renderCenterOfTextAt(centerX, centerY + 120);

    }

    //Update screen
    SDL_RenderPresent( gRenderer );
}

void GameState::handleGameplayInput() {
    //Handle events on queue
    while( SDL_PollEvent( &event ) != 0 )
    {
        if ( event.type == SDL_CONTROLLERDEVICEADDED) {
            controller = SDL_GameControllerOpen( event.cdevice.which );
            controllers.insert( { SDL_JoystickInstanceID(SDL_GameControllerGetJoystick(controller)), new Controller(controller) } );
        }

        else if ( event.type == SDL_CONTROLLERDEVICEREMOVED) {
            if (controllers.count(event.cdevice.which)) {
                controller = controllers.at( event.cdevice.which )->getController();
                SDL_GameControllerClose( controller );
                controllers.erase(event.cdevice.which);
            }
        }

        else if ( event.type == SDL_CONTROLLERAXISMOTION) {
            controllers.at(event.cdevice.which)->handleEvent(&event);
        }

        else if (event.type == SDL_CONTROLLERBUTTONDOWN) {
            gameController = controllers.at(event.cdevice.which);
            if (event.cbutton.button == SDL_CONTROLLER_BUTTON_START) {
                if (gameController->getDude()!=nullptr) {
                    gameController->getDude()->setHumanControlled(false);
                    gameController->setDude(nullptr);
                }
                else if (nextAvailableDude()!=nullptr) {
                    gameController->setDude(nextAvailableDude());
                    gameController->getDude()->setHumanControlled(true);
                }
            }
            else {
                gameController->handleEvent(&event);
            }
        }

        else if (event.type == SDL_CONTROLLERBUTTONUP) {
            controllers.at(event.cdevice.which)->handleEvent(&event);
        }

        //User requests quit
        else if( event.type == SDL_QUIT )
        {
            quit = true;
        }

         //If a key was pressed
        else if( event.type == SDL_KEYDOWN && event.key.repeat == 0 )
        {
            if (event.key.keysym.sym == SDLK_ESCAPE) {
                escMenu = !escMenu;
                pause = !pause;
            }

            if (!escMenu) {
                if (keyBoardController->getDude()==nullptr) {
                    if (nextAvailableDude()!=nullptr) {
                        keyBoardController->setDude( nextAvailableDude() );
                        keyBoardController->getDude()->setHumanControlled(true);
                    }
                }
                switch( event.key.keysym.sym ) {
                    case SDLK_q:
                        if (keyBoardController!=nullptr) {
                            keyBoardController->getDude()->setHumanControlled(false);
                            keyBoardController->setDude(nullptr);
                        }
                        break;

                    case SDLK_w:
                        keyBoardController->setUp(true);
                        break;
                    case SDLK_a:
                        keyBoardController->setLeft(true);
                        break;
                    case SDLK_s:
                        keyBoardController->setDown(true);
                        break;
                    case SDLK_d:
                        keyBoardController->setRight(true);
                        break;
                    default:
                        keyBoardController->setAction(true);
                        break;
                }
            }

            else if (escMenu) {
                pause = true;
                switch( event.key.keysym.sym ) {
                    case SDLK_q:

                    break;

                    case SDLK_f:
                    fullScreen = !fullScreen;
                    SDL_SetWindowFullscreen(gWindow, fullScreen);
                    SDL_ShowCursor(!fullScreen);
                    break;

                    case SDLK_x:
                        quit = true;
                    break;

                    case SDLK_0:
                         GameGlobals::setSoundVolume(0);
                    break;

                    case SDLK_1:
                        GameGlobals::setSoundVolume(1);
                    break;

                    case SDLK_2:
                        GameGlobals::setSoundVolume(2);
                    break;

                    case SDLK_3:
                        GameGlobals::setSoundVolume(3);
                    break;

                    case SDLK_4:
                        GameGlobals::setSoundVolume(4);
                    break;

                    case SDLK_5:
                        GameGlobals::setSoundVolume(5);
                    break;
                }
            }
        }

        //If a key was released
        else if( event.type == SDL_KEYUP && event.key.repeat == 0 )
        {
            switch( event.key.keysym.sym )
            {
                case SDLK_w:
                    keyBoardController->setUp(false);
                    break;
                case SDLK_a:
                    keyBoardController->setLeft(false);
                    break;
                case SDLK_s:
                    keyBoardController->setDown(false);
                    break;
                case SDLK_d:
                    keyBoardController->setRight(false);
                    break;
                default:
                    keyBoardController->setAction(false);
                    break;
            }
        }
    }
}

void GameState::playLoop()
{
    Uint32 perSecond = 0;
    int fps = 0;
    int physics_frames = 0;
    currentTicks = SDL_GetTicks();
    nextFrame = SDL_GetTicks();

    while( !quit ){
        fps++;
        currentTicks = SDL_GetTicks();
        //execute physics and render next frame if enough time has passed
        if (currentTicks - frameDelay > nextFrame) {
            //update the clock
            nextFrame = currentTicks;

            physics_frames++;

            //move everything
            move();

            //draw everything
            render();
        }

        handleGameplayInput();

        if (currentTicks - 1000 > perSecond) {
            printf("%d loops per second, %d physics frames per second\n",fps,physics_frames);
            perSecond = currentTicks;
            fps = 0;
            physics_frames = 0;
        }
    }
}

ExampleDude* GameState::nextAvailableDude()
{
    for (long long unsigned int i = 0; i<dudes.size(); i++) {
        if (dudes[i]!=nullptr && !dudes[i]->getHumanControlled()) {
            return dudes[i];
        }
    }
    return nullptr;
}

GameState::~GameState()
{
    delete volumeToggleString;
    delete fullscreenString;
    delete quitString;
    delete exitString;
    delete resumeString;
}
