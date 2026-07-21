#ifndef SYOBON_CROSSPLATFORM_H
#define SYOBON_CROSSPLATFORM_H

//This header is to fix non-portable functions with a cross-platform alternative
//Note that some functions are replaced by #defines, be careful
//Also note that this header must be included after every other header!

#include <unordered_set>

#ifndef SYOBON_DXLIB_H
    #error "You must include DxLib.h before this header"
#endif

#ifdef __EMSCRIPTEN__ //Emscripten

    #include <emscripten.h>

    //+KZ: Dont use SDL_Delay, emscripten handles FPS by itself
    #define SyobonWait(i)

    //+KZ: Emscripten needs a custom WaitKey, otherwise the website will freeze
    void Emscripten_WaitKey();
	#define WaitKey() Emscripten_WaitKey()

    //+KZ: Loop works differently
    void MainloopEmscripten();

    //+KZ: Emscripten does not implement SDL_SetColorKey
    //Empscripten_SetColorKey is a cheap (which means bad :p) replacement for it
    void Empscripten_SetColorKey(SDL_Surface *pSurface, Uint32 Color);
    #define SDL_SetColorKey(surface, flags, color) Empscripten_SetColorKey(surface, color)

    //+KZ: we must put WaitKey in a different place
    #define SYOBON_WAIT_KEY_MSGBOX_FIX

    #define SYOBONKZ_EMSCRIPTEN_SAVEPATH "/SyobonKZ"

#else //Everything else

    #ifdef __ANDROID__
        bool HandleAppEvents(void *userdata, SDL_Event *event);
        void DrawTouchControls();
        void HandleTouchInput(SDL_Event * event);
    #endif

    #define SyobonWait(i) SDL_Delay(i)
#endif

void MainLoop();
void UpdateKeys();
void ReleaseKeys();
const char * GetSavePath();
const char * GetBasePath();

#endif
