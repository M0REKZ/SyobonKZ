//+KZ: OMG SDL13-compat!!! nah, just for what we need

#ifdef SYOBONKZ_USE_SDL3
	#include <SDL3/SDL.h>
	#include <SDL3_image/SDL_image.h>
	#include <SDL3_mixer/SDL_mixer.h>
	#include <SDL3_ttf/SDL_ttf.h>
    #include <SDL3_gfx/SDL3_rotozoom.h>
    #include <SDL3_gfx/SDL3_gfxPrimitives.h>

    extern SDL_Window * pWindow;
    extern MIX_Track * pBGMTrack;
    extern SDL_Renderer * pRenderer;
    extern MIX_Mixer * pMixer;

    #define SyobonKZSDLInit(flags) (SDL_Init(flags) == false ? -1 : 0)

    #define SyobonKZChunk MIX_Audio
    #define SyobonKZMusic MIX_Audio

    #define SyobonKZLoadChunk(chunk) MIX_LoadAudio(pMixer, chunk, true)
    #define SyobonKZLoadMusic(mus) MIX_LoadAudio(pMixer, mus, false)

    #define SyobonKZGetSDLMixError() SDL_GetError()

    #define SyobonKZPlayChunk(channel, chunk, loops) {  \
        MIX_PlayAudio(pMixer, chunk);   \
    }
    #define SyobonKZPlayMusic(chunk, loops) {  \
        pBGMTrack = MIX_CreateTrack(pMixer);    \
        if(MIX_SetTrackAudio(pBGMTrack, chunk))    \
        {   \
            SDL_PropertiesID props = SDL_CreateProperties();    \
            SDL_SetNumberProperty(props, MIX_PROP_PLAY_LOOPS_NUMBER, loops);   \
            MIX_PlayTrack(pBGMTrack, props);    \
        }   \
    }
    #define SyobonKZHaltChannel(channel) /*not implemented*/
    #define SyobonKZHaltMusic() MIX_StopTrack(pBGMTrack, 0)
    #define SyobonKZVolumeMusic(volume) MIX_SetTrackGain(pBGMTrack, (volume) / 128)
    #define SYOBONKZ_MAX_VOLUME (float)128 // MIX_MAX_VOLUME is 128
    #define SYOBONKZ_AUDIO_FORMAT SDL_AUDIO_S16
    #define SyobonKZFreeChunk(chunk) MIX_DestroyAudio(chunk)
    #define SyobonKZFreeMusic(chunk) MIX_DestroyAudio(chunk)

    bool SyobonKZOpenAudio(int frequency, Uint16 format, int nchannels, int chunksize);
    #define SyobonKZAudioQuit() MIX_Quit()

    #define SyobonKZFillRect(surface, rect, color) SDL_FillSurfaceRect(surface, rect, color)
    #define SyobonKZFilledEllipseColor(surface, x, y, rx, ry, color) filledEllipseColor(pRenderer, x, y, rx, ry, color);
    #define SyobonKZEllipseColor(surface, x, y, rx, ry, color) ellipseColor(pRenderer, x, y, rx, ry, color);
    #define SyobonKZBoxColor(surface, x, y, x2, y2, color) boxColor(pRenderer, x, y, x2, y2, color);
    #define SyobonKZRectangleColor(surface, x, y, x2, y2, color) rectangleColor(pRenderer, x, y, x2, y2, color);
    #define SyobonKZLineColor(surface, x, y, x2, y2, color) lineColor(pRenderer, x, y, x2, y2, color);
    #define SyobonKZPixelColor(surface, x, y, color) SDL_WriteSurfacePixel(surface, x, y, (color >> 8 * 3) & 0xFF, (color >> 8 * 2) & 0xFF, (color >> 8) & 0xFF, color & 0xFF)

    #define SyobonKZLoadImage(image) SDL_LoadSurface(image)
    #define SyobonKZFreeImage(image) SDL_DestroySurface(image)

    #define SyobonKZGetSDLImgError() SDL_GetError()

    #define SyobonKZImageInit(flags) flags
    #define SyobonKZImageQuit()

    #define SYOBONKZ_IMAGE_INIT_PNG 0

    SDL_Surface * SyobonKZZoomSurface(SDL_Surface * image, double zoomx, double zoomy, int smooth);
    #define SyobonKZSetColorKey(image, key) SDL_SetSurfaceColorKey(image, true, key)

    #define SyobonKZCreateSurface(flags, width, height, pixelformat) \
    SDL_CreateSurface(width, height, pixelformat)

    #define SyobonKZSetWindowTitle(title, iconname) SDL_SetWindowTitle(pWindow, title)

    #define SyobonKZShowCursor(show) {if(show)SDL_ShowCursor();else SDL_HideCursor();}

    #define SyobonKZGetSDLTTFError() SDL_GetError()

    #define SyobonKZJoystickOpen(n) SDL_OpenJoystick(n)
    #define SyobonKZJoystickClose(n) SDL_CloseJoystick(n)
    #define SyobonKZJoystickGetButton(n, btn) SDL_GetJoystickButton(n, btn)

    #define SYOBONKZ_EVENT_KEYDOWN SDL_EVENT_KEY_DOWN
    #define SYOBONKZ_EVENT_KEYUP SDL_EVENT_KEY_UP
    #define SYOBONKZ_EVENT_JOYAXISMOTION SDL_EVENT_JOYSTICK_AXIS_MOTION
    #define SYOBONKZ_EVENT_QUIT SDL_EVENT_QUIT

    #define SYOBONKZ_KEY_EVENT_SDL_ALIAS event.key.key

    #define SYOBONKZ_SDL_INIT_EVERYTHING (SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_EVENTS \
        | SDL_INIT_JOYSTICK | SDL_INIT_HAPTIC | SDL_INIT_GAMEPAD | SDL_INIT_SENSOR)

    #define SyobonKZTTFInit() (TTF_Init() == false ? -1 : 0)
    #define SyobonKZRenderUTF8Text(font, text, color) TTF_RenderText_Solid(font, text, strlen(text), color)

    #define SYOBON_COLOR_KEY(img) SDL_MapRGB(SDL_GetPixelFormatDetails(img), nullptr, 9 * 16 + 9, 255, 255)

    //DxLib.h
    #define GetColor(r, g, b) SDL_MapSurfaceRGB(screen, r, g, b)
    #define SyobonKZScreenFlip(screensurface) {  \
        SDL_Surface *pWindowSurface = SDL_GetWindowSurface(pWindow);    \
        SDL_Rect srcrect, destrect;  \
        srcrect.x = 0; srcrect.y = 0; srcrect.w = 480; srcrect.h = 420; \
        destrect.x = 0; destrect.y = 0; destrect.w = pWindowSurface->w; destrect.h = pWindowSurface->h; \
        SDL_BlitSurface(screensurface, &srcrect, pWindowSurface, &destrect);    \
        SDL_UpdateWindowSurface(pWindow);   \
    }

    //Key Aliases
    #define KEY_INPUT_ESCAPE SDLK_ESCAPE
    #define KEY_INPUT_LEFT SDLK_LEFT
    #define KEY_INPUT_RIGHT SDLK_RIGHT
    #define KEY_INPUT_DOWN SDLK_DOWN
    #define KEY_INPUT_UP SDLK_UP
    #define KEY_INPUT_F1 SDLK_F1
    #define KEY_INPUT_O SDLK_O
    #define KEY_INPUT_Z SDLK_Z
    #define KEY_INPUT_RETURN SDLK_RETURN
    #define KEY_INPUT_SPACE SDLK_SPACE
    #define KEY_INPUT_1 SDLK_1
    #define KEY_INPUT_2 SDLK_2
    #define KEY_INPUT_3 SDLK_3
    #define KEY_INPUT_4 SDLK_4
    #define KEY_INPUT_5 SDLK_5
    #define KEY_INPUT_6 SDLK_6
    #define KEY_INPUT_7 SDLK_7
    #define KEY_INPUT_8 SDLK_8
    #define KEY_INPUT_9 SDLK_9
    #define KEY_INPUT_0 SDLK_0
#else
	#include <SDL.h>
	#include <SDL_rotozoom.h>
	#include <SDL_gfxPrimitives.h>
	#include <SDL_image.h>
	#include <SDL_mixer.h>
	#include <SDL_ttf.h>

    #define SyobonKZSDLInit(flags) SDL_Init(flags)

    #define SyobonKZChunk Mix_Chunk
    #define SyobonKZMusic Mix_Music

    #define SyobonKZLoadChunk(chunk) Mix_LoadWAV(chunk)
    #define SyobonKZLoadMusic(mus) Mix_LoadMUS(mus)

    #define SyobonKZGetSDLMixError() Mix_GetError()

    #define SyobonKZPlayChunk(channel, chunk, loops) Mix_PlayChannel(channel, chunk, loops)
    #define SyobonKZPlayMusic(music, loops) Mix_PlayMusic(music, loops)
    #define SyobonKZHaltChannel(channel) Mix_HaltChannel(channel)
    #define SyobonKZHaltMusic() Mix_HaltMusic()
    #define SyobonKZVolumeMusic(volume) Mix_VolumeMusic(volume)
    #define SYOBONKZ_MAX_VOLUME MIX_MAX_VOLUME
    #define SYOBONKZ_AUDIO_FORMAT AUDIO_S16LSB
    #define SyobonKZFreeChunk(chunk) Mix_FreeChunk(chunk)
    #define SyobonKZFreeMusic(chunk) Mix_FreeMusic(chunk)

    #define SyobonKZOpenAudio(frequency, format, nchannels, chunksize) Mix_OpenAudio(frequency, format, nchannels, chunksize)
    #define SyobonKZAudioQuit() Mix_Quit()

    #define SyobonKZFillRect(surface, rect, color) SDL_FillRect(surface, rect, color)
    #define SyobonKZFilledEllipseColor(surface, x, y, rx, ry, color) filledEllipseColor(surface, x, y, rx, ry, color)
    #define SyobonKZEllipseColor(surface, x, y, rx, ry, color) ellipseColor(surface, x, y, rx, ry, color)
    #define SyobonKZBoxColor(surface, x, y, x2, y2, color) boxColor(surface, x, y, x2, y2, color)
    #define SyobonKZRectangleColor(surface, x, y, x2, y2, color) rectangleColor(surface, x, y, x2, y2, color)
    #define SyobonKZLineColor(surface, x, y, x2, y2, color) lineColor(surface, x, y, x2, y2, color) 
    #define SyobonKZPixelColor(screen, x, y, color) pixelColor(screen, x, y, color)

    #define SyobonKZLoadImage(image) SDL_LoadSurface(image)
    #define SyobonKZFreeImage(image) SDL_FreeSurface(image)

    #define SyobonKZGetSDLImgError() IMG_GetError()
    #define SyobonKZImageInit(flags) IMG_Init(flags)
    #define SyobonKZImageQuit() IMG_Quit()

    #define SYOBONKZ_IMAGE_INIT_PNG IMG_INIT_PNG

    #define SyobonKZZoomSurface(image, zoomx, zoomy, smooth) zoomSurface(image, zoomx, zoomy, smooth)
    #define SyobonKZSetColorKey(image, key) SDL_SetColorKey(image, SDL_SRCCOLORKEY, key)

    #define SyobonKZCreateSurface(flags, width, height, pixelformat) \
    SDL_CreateRGBSurface(SDL_SWSURFACE, width, height, pixelformat->BitsPerPixel, pixelformat->Rmask, pixelformat->Bmask, pixelformat->Gmask, pixelformat->Amask)
    
    #define SyobonKZSetWindowTitle(title, iconname) SDL_WM_SetCaption(title, iconname)

    #define SyobonKZShowCursor(show) SDL_ShowCursor(show)

    #define SyobonKZGetSDLTTFError() TTF_GetError()

    #define SyobonKZJoystickOpen(n) SDL_JoystickOpen(n)
    #define SyobonKZJoystickClose(n) SDL_JoystickClose(n)
    #define SyobonKZJoystickGetButton(n, btn) SDL_JoystickGetButton(n, btn)

    #define SYOBONKZ_EVENT_KEYDOWN SDL_KEYDOWN
    #define SYOBONKZ_EVENT_KEYUP SDL_KEYUP
    #define SYOBONKZ_EVENT_JOYAXISMOTION SDL_JOYAXISMOTION
    #define SYOBONKZ_EVENT_QUIT SDL_QUIT

    #define SYOBONKZ_KEY_EVENT_SDL_ALIAS event.key.keysym.sym

    #define SYOBONKZ_SDL_INIT_EVERYTHING SDL_INIT_EVERYTHING

    #define SyobonKZTTFInit() TTF_Init()
    #define SyobonKZRenderUTF8Text(font, text, color) TTF_RenderUTF8_Solid(font, text, color)

    #define SYOBON_COLOR_KEY(img) SDL_MapRGB(img, 9 * 16 + 9, 255, 255)

    //DxLib.h
    #define GetColor(r, g, b) SDL_MapRGB(screen->format, r, g, b)
    #define SyobonKZScreenFlip(screensurface) SDL_Flip(screensurface)

    //Key Aliases
    #define KEY_INPUT_ESCAPE SDLK_ESCAPE
    #define KEY_INPUT_LEFT SDLK_LEFT
    #define KEY_INPUT_RIGHT SDLK_RIGHT
    #define KEY_INPUT_DOWN SDLK_DOWN
    #define KEY_INPUT_UP SDLK_UP
    #define KEY_INPUT_F1 SDLK_F1
    #define KEY_INPUT_O SDLK_o
    #define KEY_INPUT_Z SDLK_z
    #define KEY_INPUT_RETURN SDLK_RETURN
    #define KEY_INPUT_SPACE SDLK_SPACE
    #define KEY_INPUT_1 SDLK_1
    #define KEY_INPUT_2 SDLK_2
    #define KEY_INPUT_3 SDLK_3
    #define KEY_INPUT_4 SDLK_4
    #define KEY_INPUT_5 SDLK_5
    #define KEY_INPUT_6 SDLK_6
    #define KEY_INPUT_7 SDLK_7
    #define KEY_INPUT_8 SDLK_8
    #define KEY_INPUT_9 SDLK_9
    #define KEY_INPUT_0 SDLK_0
#endif

//Common / Translated without macros:

#define SYOBONKZ_SDL_FULLSCREEN 0x80000000
#define SYOBONKZ_SDL_RESIZABLE 0x00000010
#define SYOBONKZ_SDL_DOUBLEBUF 0x40000000
#define SYOBONKZ_SDL_SWSURFACE 0
#define SYOBONKZ_SDL_DISABLE 0

SDL_Surface * SyobonKZCreateWindow(int width, int height, int bpp, Uint32 flags);
SDL_Surface * SyobonKZFixImage(SDL_Surface * image, const char *filename);
