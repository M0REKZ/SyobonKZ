
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

    #ifdef __ANDROID__

    bool HandleAppEvents(void *userdata, SDL_Event *event)
    {
        switch (event->type)
        {
        case SDL_EVENT_TERMINATING:
            /* Terminate the app.
            Shut everything down before returning from this function.
            */
            return false;
        case SDL_EVENT_LOW_MEMORY:
            /* You will get this when your app is paused and Android wants more memory.
            Release as much memory as possible.
            */
            return false;
        case SDL_EVENT_WILL_ENTER_BACKGROUND:
            /* Prepare your app to go into the background.  Stop loops, etc.
            This gets called when the user hits the home button, or gets a call.

            You should not make any OpenGL graphics calls or use the rendering API,
            in addition, you should set the render target to NULL, if you're using
            it, e.g. call SDL_SetRenderTarget(renderer, NULL).
            */
            return false;
        case SDL_EVENT_DID_ENTER_BACKGROUND:
            /* Your app is NOT active at this point. */
            return false;
        case SDL_EVENT_WILL_ENTER_FOREGROUND:
            /* This call happens when your app is coming back to the foreground.
            Restore all your state here.
            */
            return false;
        case SDL_EVENT_DID_ENTER_FOREGROUND:
            /* Restart your loops here.
            Your app is interactive and getting CPU again.

            You have access to the OpenGL context or rendering API at this point.
            However, there's a chance (on older hardware, or on systems under heavy load),
            where the graphics context cannot be restored. You should listen for the
            event SDL_EVENT_RENDER_DEVICE_RESET and recreate your OpenGL context and
            restore your textures when you get it, or quit the app.
            */
            return false;
        default:
            /* No special processing, add it to the event queue */
            return true;
        }
    }

    SDL_Rect LeftButton, RightButton, DownButton, JumpButton;

    void UpdateTouchControls()
    {
        SDL_Surface *pWindowSurface = SDL_GetWindowSurface(pWindow);

        //simple way to detect if phone is landscape so we put the buttons in a better position
        bool Landscape = pWindowSurface->w > pWindowSurface->h;

        int ButtonsSizeY = Landscape ? 150 : 130;
        int ButtonsStartX = Landscape ? 75 : 25;
        int ButtonsStartY = pWindowSurface->h - ((Landscape ? 75 : 256) + ButtonsSizeY * 2);

        //Left
        LeftButton = {ButtonsStartX, ButtonsStartY, ButtonsSizeY + ButtonsSizeY/2, ButtonsSizeY};
        RightButton = {LeftButton.x + LeftButton.w + 6, ButtonsStartY, ButtonsSizeY + ButtonsSizeY/2, ButtonsSizeY};
        DownButton = {LeftButton.x + (LeftButton.w + 6) / 2, ButtonsStartY + ButtonsSizeY, ButtonsSizeY + ButtonsSizeY/2 + 3, ButtonsSizeY};

        //Right
        JumpButton = {pWindowSurface->w - (int)(ButtonsSizeY * 1.5f + ButtonsStartX), ButtonsStartY, (int)(ButtonsSizeY * 1.5f), (int)(ButtonsSizeY * 1.5f)};
    }

    void HandleTouchInput()
    {
        int devicecount = 0;
        SDL_TouchID * touchids = SDL_GetTouchDevices(&devicecount);
        
        if(!touchids)
            return;

        for(int j = 0; j < devicecount; ++j)
        {
            //Release keys
            SetKeyState(KEY_INPUT_LEFT, false); 
            SetKeyState(KEY_INPUT_RIGHT, false);
            SetKeyState(KEY_INPUT_DOWN, false);
            SetKeyState(KEY_INPUT_Z, false); //Jump, Start

            int count = 0;
            SDL_Finger **fingers = SDL_GetTouchFingers(touchids[j], &count);

            for(int i = 0; i < count; i ++)
            {
                SDL_Surface *pWindowSurface = SDL_GetWindowSurface(pWindow);
                const bool PressState = true;
                SDL_Point TouchedPos = {(int)(fingers[i]->x * pWindowSurface->w), (int)(fingers[i]->y * pWindowSurface->h)};

                if(SDL_PointInRect(&TouchedPos, &LeftButton))
                    SetKeyState(KEY_INPUT_LEFT, PressState); 
                else if(SDL_PointInRect(&TouchedPos, &RightButton))
                    SetKeyState(KEY_INPUT_RIGHT, PressState);
                else if(SDL_PointInRect(&TouchedPos, &DownButton))
                    SetKeyState(KEY_INPUT_DOWN, PressState); 
                else if(SDL_PointInRect(&TouchedPos, &JumpButton))
                    SetKeyState(KEY_INPUT_Z, PressState);
            }
        }
    }

    void DrawTouchControls()
    {
        SDL_Surface *pWindowSurface = SDL_GetWindowSurface(pWindow);

        Uint32 white = SDL_MapSurfaceRGBA(pWindowSurface, 255, 255, 255, 100);
        SDL_FillSurfaceRect(pWindowSurface, &LeftButton, white);
        SDL_FillSurfaceRect(pWindowSurface, &RightButton, white);
        SDL_FillSurfaceRect(pWindowSurface, &DownButton, white);
        SDL_FillSurfaceRect(pWindowSurface, &JumpButton, white);
    }

    #endif

void MainLoop()
{
    while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
    {
        #ifdef __ANDROID__
            UpdateTouchControls();
            HandleTouchInput();
        #endif
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
            if (event.type == SYOBONKZ_EVENT_KEYDOWN
            #ifdef __ANDROID__
            || event.type == SDL_EVENT_FINGER_DOWN
            #endif
            )
                return SYOBONKZ_KEY_EVENT_SDL_ALIAS;
    }
}

void UpdateKeys()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SYOBONKZ_EVENT_KEYDOWN:
            SetKeyState(SYOBONKZ_KEY_EVENT_SDL_ALIAS, true);
            break;
        case SYOBONKZ_EVENT_KEYUP:
            SetKeyState(SYOBONKZ_KEY_EVENT_SDL_ALIAS, false);
            break;
        case SYOBONKZ_EVENT_JOYAXISMOTION:
            if (event.jaxis.which == 0)
            {
                if (event.jaxis.axis == JOYSTICK_XAXIS)
                {
                    if (event.jaxis.value < 0)
                        SetKeyState(SDLK_LEFT, true);
                    else if (event.jaxis.value > 0)
                        SetKeyState(SDLK_RIGHT, true);
                    else
                    {
                        SetKeyState(SDLK_LEFT, false);
                        SetKeyState(SDLK_RIGHT, false);
                    }
                }
                else if (event.jaxis.axis == JOYSTICK_YAXIS)
                {
                    if (event.jaxis.value < 0)
                        SetKeyState(SDLK_UP, true);
                    else if (event.jaxis.value > 0)
                        SetKeyState(SDLK_DOWN, true);
                    else
                    {
                        SetKeyState(SDLK_UP, false);
                        SetKeyState(SDLK_DOWN, false);
                    }
                }
            }
            break;
        case SYOBONKZ_EVENT_QUIT:
            DxLibExit = true;
            break;
        }
    }
}

#endif