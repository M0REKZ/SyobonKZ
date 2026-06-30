#include <cstdio>

#include "sdl_includer.h"

#ifdef SYOBONKZ_USE_SDL3

    SDL_Window * pWindow = nullptr;
    SDL_Renderer * pRenderer = nullptr;
    SDL_Renderer * pWindowRenderer = nullptr;
    MIX_Track * pBGMTrack = nullptr;
    MIX_Mixer * pMixer = nullptr;
    MIX_Track * apSETracks[8] = { /* in SDL 1.2 MIX_CHANNELS is 8 */
        nullptr, nullptr, nullptr, nullptr,
        nullptr, nullptr, nullptr, nullptr
    };
    SDL_Texture * pTexture = nullptr;
    SDL_PixelFormat PixelFormat;

    SDL_Surface *SyobonKZZoomSurface(SDL_Surface *image, double zoomx, double zoomy, int smooth)
    {
        SDL_Surface * zoomed = SDL_CreateSurface(image->w, image->h, SDL_PIXELFORMAT_RGBA8888);

        if(!zoomed)
        {
            fprintf(stderr, "Error: unable to zoom surface %p: %s\n", image, SDL_GetError());
        }

        SDL_Rect srcrect;
        srcrect.x = srcrect.y = 0;
        srcrect.w = image->w;
        srcrect.h = image->h;

        SDL_Rect destrect;
        destrect.x = destrect.y = 0;
        destrect.w = SDL_abs(image->w * zoomx);
        destrect.h = SDL_abs(image->h * zoomy);

        SDL_BlitSurface(image, &srcrect, zoomed, &destrect);
        SDL_FlipSurface(zoomed,
            zoomx < 0 ? (zoomy < 0 ? SDL_FLIP_HORIZONTAL_AND_VERTICAL :
            SDL_FLIP_HORIZONTAL) : (zoomy < 0 ? SDL_FLIP_VERTICAL :
            SDL_FLIP_NONE)
        );

        return zoomed;
    }

    bool SyobonKZOpenAudio(int frequency, Uint16 format, int nchannels, int chunksize)
    {
        MIX_Init();

        SDL_AudioSpec spec;
        SDL_zero(spec);
        spec.freq = frequency;
        spec.format = (SDL_AudioFormat)format;
        spec.channels = nchannels;

        pMixer = MIX_CreateMixerDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, &spec);
        return pMixer == 0;
    }
#endif

void SyobonKZQuit()
{
    #ifdef SYOBONKZ_USE_SDL3

        //Destroy all weird things we created here for SDL3
        //
        //pWindowSurface is not here

        //Texture 480x420 for faster rendering
        if(pTexture)
        {
            SDL_DestroyTexture(pTexture);
        }

        //Renderer for 480x420 game surface (only for SDL3_gfx.....)
        if(pRenderer)
        {
            SDL_DestroyRenderer(pRenderer);
        }

        //window renderer (full screen)
        if(pWindowRenderer)
        {
            SDL_DestroyRenderer(pWindowRenderer);
        }

        //finally the window
        if(pWindow)
        {
            SDL_DestroyWindow(pWindow);
        }

    #endif

    //SDL_Quit is called the same way in SDL 1.2 and SDL3
    return SDL_Quit();
}

SDL_Surface *SyobonKZCreateWindow(int width, int height, int bpp, Uint32 flags)
{
    #ifndef SYOBONKZ_USE_SDL3
        return SDL_SetVideoMode(width, height, bpp, flags);
    #else

        SDL_WindowFlags newflags = 0;

        //translate the SDL 1.2 flags we use
        if(flags & SYOBONKZ_SDL_RESIZABLE)
            newflags = SDL_WINDOW_RESIZABLE;
        if(flags & SYOBONKZ_SDL_FULLSCREEN)
            newflags = SDL_WINDOW_FULLSCREEN;

        pWindow = SDL_CreateWindow("", width, height, newflags);
        
        if(!pWindow)
        {
            fprintf(stderr, "SyobonKZCreateWindow - Unable to create pWindow: %s\n", SDL_GetError());
            return nullptr;
        }

        //We need to copy the surface to this texture for faster rendering
        pWindowRenderer = SDL_GetRenderer(pWindow);

        if(!pWindowRenderer)
        {
            printf("SyobonKZCreateWindow - SDL_GetRenderer returned NULL for pWindowRenderer, trying to create a new Renderer...\n");

            pWindowRenderer = SDL_CreateRenderer(pWindow, nullptr);

            if(!pWindowRenderer)
            {
                fprintf(stderr, "SyobonKZCreateWindow - Unable to create pWindowRenderer: %s\n", SDL_GetError());
                return nullptr;
            }
        }

        //hacky way to get pixel format from renderer
        //i dont want to overcomplicate my life and Simple Direct Media Layer 3 is NOT simple! >:(
        SDL_Rect TempRect = {0,0,1,1};
        SDL_Surface * pTempRendererSurface = SDL_RenderReadPixels(pWindowRenderer, &TempRect);
        if(!pTempRendererSurface)
        {
            fprintf(stderr, "SyobonKZCreateWindow - Unable to create pTempRendererSurface: %s\n", SDL_GetError());
            return nullptr;
        }
        PixelFormat = pTempRendererSurface->format;
        SDL_DestroySurface(pTempRendererSurface);

        //This will be the game screen
        SDL_Surface * pWindowSurface = SDL_CreateSurface(width, height, PixelFormat);

        if(!pWindowSurface)
        {
            fprintf(stderr, "SyobonKZCreateWindow - Unable to create pWindowSurface: %s\n", SDL_GetError());
            return nullptr;
        }

        //SDL3_gfx needs a renderer to draw on
        pRenderer = SDL_CreateSoftwareRenderer(pWindowSurface);

        if(!pRenderer)
        {
            fprintf(stderr, "SyobonKZCreateWindow - Unable to create pRenderer: %s\n", SDL_GetError());
            return nullptr;
        }

        pTexture = SDL_CreateTexture(pWindowRenderer, PixelFormat,
        SDL_TEXTUREACCESS_STREAMING, 480, 420);

        if(!pTexture)
        {
            fprintf(stderr, "SyobonKZCreateWindow - Unable to create pWindowRenderer: %s\n", SDL_GetError());
            return nullptr;
        }

        SDL_SetTextureScaleMode(pTexture, SDL_SCALEMODE_NEAREST);

        return pWindowSurface;
    #endif
}

SDL_Surface *SyobonKZFixImage(SDL_Surface * image, const char *filename)
{
    #ifdef SYOBONKZ_USE_SDL3
        static SDL_PixelFormat fmt;
        static char setfmt = 0;
        if (!setfmt)
        {
            fmt = (image->format);
            setfmt = 1;
        }
        const SDL_PixelFormatDetails * newfmt = SDL_GetPixelFormatDetails(image->format);

        if (newfmt && newfmt->bytes_per_pixel != 1)
        {
            printf("WARNING: %s pixel format is not the one required, trying to fix...\n", filename);

            SDL_Surface *newimage = SDL_CreateSurface(image->w, image->h, SDL_PIXELFORMAT_RGBA8888);
            if (newimage)
            {
                SDL_Rect srcrect, destrect;
                srcrect.x = 0; srcrect.y = 0; srcrect.w = image->w; srcrect.h = image->w;
                destrect.x = 0; destrect.y = 0; destrect.w = newimage->w; destrect.h = newimage->h;
                SDL_BlitSurface(image, &srcrect, newimage, &destrect);
                printf("Successfully converted\n");
                SyobonKZFreeImage(image);
                image = newimage;
                newimage = nullptr;
            }
            else
            {
                printf("Conversion failed: %s\n", SDL_GetError());
            }
        }
    #else
        static SDL_PixelFormat fmt;
        static char setfmt = 0;
        if (!setfmt)
        {
            fmt = *(image->format);
            setfmt = 1;
        }
        SDL_PixelFormat newfmt = *(image->format);

        if (newfmt.BytesPerPixel != 1)
        {
            printf("WARNING: %s pixel format is not the one required, trying to fix...\n", filename);

            SDL_Surface *newimage = SDL_ConvertSurface(image, &fmt, SDL_SWSURFACE | SDL_SRCALPHA | SDL_SRCCOLORKEY);
            if (newimage)
            {
                printf("Successfully converted\n");
                SyobonKZFreeImage(image);
                image = newimage;
                newimage = nullptr;
            }
            else
            {
                printf("Conversion failed: %s\n", SDL_GetError());
            }
        }
    #endif

    return image;
}
