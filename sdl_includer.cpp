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
            return nullptr;

        SDL_Surface *pRealWindowSurface = SDL_GetWindowSurface(pWindow);

        if(!pRealWindowSurface)
            return nullptr;

        SDL_Surface * pWindowSurface = SDL_CreateSurface(width, height, pRealWindowSurface->format);

        if(!pWindowSurface)
            return nullptr;

        //SDL3_gfx needs a renderer to draw on
        pRenderer = SDL_CreateSoftwareRenderer(pWindowSurface);

        //We need to copy the surface to this texture for faster rendering
        pWindowRenderer = SDL_GetRenderer(pWindow);

        if(!pWindowRenderer)
            return nullptr;

        pTexture = SDL_CreateTexture(pWindowRenderer, pRealWindowSurface->format,
        SDL_TEXTUREACCESS_STREAMING, 480, 420);

        if(!pTexture)
            return nullptr;

        SDL_SetTextureScaleMode(pTexture, SDL_SCALEMODE_NEAREST);

        if(!pRenderer)
            return nullptr;

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
