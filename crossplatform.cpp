
#include "DxLib.h"
#include "main.h"
#include "global_vars.h"

#include "crossplatform.h"

#ifdef __EMSCRIPTEN__ // Emscripten

void MainloopEmscripten()
{
    UpdateKeys();
    SyobonQuit = 0;
    Mainprogram();
    if (SyobonQuit == 3)
        return;
    static int prevFPS = 30;
    if (prevFPS != xx[0])
    {
        // Restart the loop with a different Target FPS
        emscripten_cancel_main_loop();
        prevFPS = xx[0];
        emscripten_set_main_loop(MainloopEmscripten, xx[0], 1);
    }
}

void Empscripten_SetColorKey(SDL_Surface *pSurface, Uint32 Color)
{
    SDL_LockSurface(pSurface);

    union PixelColor32
    {
        Uint32 Pixel;
        Uint8 Colors[4];
    };

    PixelColor32 ColorKey;
    ColorKey.Pixel = Color;

    // Pixels are weird in emscripten for some reason and does not match exact value
    //(or it is just me being bad at Emscripten SDL)
    int Tolerance = 2;

    size_t max = pSurface->w * pSurface->h;
    for (int i = 0; i < max; ++i)
    {
        SDL_Color *pPixel = &((SDL_Color *)pSurface->pixels)[i];

        if (
            pPixel->r >= ColorKey.Colors[0] - Tolerance && pPixel->r < ColorKey.Colors[0] + Tolerance &&
            pPixel->g >= ColorKey.Colors[1] - Tolerance && pPixel->g < ColorKey.Colors[1] + Tolerance &&
            pPixel->b >= ColorKey.Colors[2] - Tolerance && pPixel->b < ColorKey.Colors[2] + Tolerance)
        {
            *((Uint32 *)pPixel) = 0;
        }
    }

    SDL_UnlockSurface(pSurface);
}

//+KZ: Emscripten needs a custom WaitKey, otherwise the browser will freeze
void Emscripten_WaitKey_Loop(void *args /* (args is not used and should not be) */)
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_KEYDOWN)
        {
            return;
        }
    }
    //+KZ: keep pushing ourselves until a key is pressed
    emscripten_push_main_loop_blocker(Emscripten_WaitKey_Loop, nullptr);
}

//+KZ: starts the WaitKey loop
void Emscripten_WaitKey()
{
    emscripten_push_main_loop_blocker(Emscripten_WaitKey_Loop, nullptr);
}

#else

void MainLoop()
{
    while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
    {
        UpdateKeys();
        SyobonQuit = 0;
        Mainprogram();
        if (SyobonQuit == 3)
            break;
    }
}

byte WaitKey()
{
    SDL_Event event;
    while (true)
    {
        while (SDL_PollEvent(&event))
            if (event.type == SYOBONKZ_EVENT_KEYDOWN)
                return SYOBONKZ_KEY_EVENT_SDL_ALIAS;
    }
}

#endif