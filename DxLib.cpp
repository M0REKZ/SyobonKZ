
#include "DxLib.h"

#include "crossplatform.h"
#include "global_vars.h"

SDL_Joystick *joystick;

//bool keysHeld[512]; //+KZ: This breaks with SDL3, using sKeysHeld instead
struct sKeysHeld
{
    //keys in the header
    bool KEY_ESCAPE = false;
    bool KEY_LEFT = false;
    bool KEY_RIGHT = false;
    bool KEY_DOWN = false;
    bool KEY_UP = false;
    bool KEY_F1 = false;
    bool KEY_O = false;
    bool KEY_Z = false;
    bool KEY_RETURN = false;
    bool KEY_SPACE = false;
    bool KEY_1 = false;
    bool KEY_2 = false;
    bool KEY_3 = false;
    bool KEY_4 = false;
    bool KEY_5 = false;
    bool KEY_6 = false;
    bool KEY_7 = false;
    bool KEY_8 = false;
    bool KEY_9 = false;
    bool KEY_0 = false;

    //other keys
    bool KEY_SEMICOLON = false;
} keysHeld;
bool sound = true;
void deinit();
int DxLib_Init()
{
    atexit(deinit);
    setlocale(LC_CTYPE, "ja_JP.UTF-8");

    if (SyobonKZSDLInit(SYOBONKZ_SDL_INIT_EVERYTHING) < 0)
    {
        fprintf(stderr, "Unable to init SDL: %s\n", SDL_GetError());
        return -1;
    }

    if (!(screen =
              SyobonKZCreateWindow(480 /*(int)fmax/100 */,
                               420 /*(int)fymax/100 */, 32,
                               SYOBONKZ_SDL_SWSURFACE | SYOBONKZ_SDL_DOUBLEBUF | SYOBONKZ_SDL_RESIZABLE | (StartFullScreenFlag ? SYOBONKZ_SDL_FULLSCREEN : 0))))
    {
        fprintf(stderr, "Unable to create SDL Window: %s\n", SDL_GetError());
        SDL_Quit();
        return -1;
    }

    SyobonKZSetWindowTitle("Syobon Action - +KZ Edition!",
                      NULL);
    SyobonKZShowCursor(SYOBONKZ_SDL_DISABLE);

    if (SyobonKZImageInit(SYOBONKZ_IMAGE_INIT_PNG) != SYOBONKZ_IMAGE_INIT_PNG)
    {
        fprintf(stderr, "Unable to init SDL_img: %s\n", SyobonKZGetSDLImgError());
        return -1;
    }

    // Initialize font
    if (SyobonKZTTFInit() == -1)
    {
        fprintf(stderr, "Unable to init SDL_ttf: %s\n", SyobonKZGetSDLTTFError());
        return -1;
    }

    // Audio Rate, Audio Format, Audio Channels, Audio Buffers
#define AUDIO_CHANNELS 2
    if (sound && SyobonKZOpenAudio(22050, SYOBONKZ_AUDIO_FORMAT, AUDIO_CHANNELS, 1024))
    {
        fprintf(stderr, "Unable to init SDL_mixer: %s\n", SyobonKZGetSDLMixError());
        sound = false;
    }
    // Try to get a joystick
    joystick = SyobonKZJoystickOpen(0);

    SDL_memset(&keysHeld, 0, sizeof(keysHeld));

    for (int i = 0; i < FONT_MAX; i++)
        font[i] = NULL;
    srand(time(NULL));

    return 0;
}

// Main screen
SDL_Surface *screen;

// Fonts
Uint8 fontsize = 0;
TTF_Font *font[FONT_MAX];

// Strings
void SetFontSize(Uint8 size)
{
    fontsize = size;
    if (font[size] == NULL)
    {
        font[size] = TTF_OpenFont("res/sazanami-gothic.ttf", size);
        if (font[size] == NULL)
        {
            printf("Unable to load font: %s\n", SyobonKZGetSDLTTFError());
            exit(1);
        }
    }
}

Uint8 fontType = DX_FONTTYPE_NORMAL;
void ChangeFontType(Uint8 type)
{
    fontType = type;
}

SDL_Surface *StringToSurface(const char *pstring, Uint32 color, Uint8 font_size, Uint8 font_type)
{
    SDL_Color temp_color = {(Uint8)(color >> 16), (Uint8)(color >> 8), (Uint8)(color)};
    SDL_Surface *rendered = SyobonKZRenderUTF8Text(font[font_size], pstring, temp_color);
    if (font_type == DX_FONTTYPE_EDGE)
    {
        //final surface
        SDL_Surface *newrendered;
        newrendered = SyobonKZCreateSurface(SDL_SWSURFACE, rendered->w + 2, rendered->h + 2, screen->format);
        newrendered = SyobonKZFixImage(newrendered, pstring);
        SyobonKZFillRect(newrendered, NULL, 0);
        if(newrendered)
        {
            //copy shadow
            SDL_Color blk = {0, 0, 0}; //forever TODO: 0,0,0 invisible?
            SDL_Surface *shadow = SyobonKZRenderUTF8Text(font[font_size], pstring, blk);
            shadow = SyobonKZFixImage(shadow, pstring);
            printf("SHADOW %p %s\n",shadow, pstring);
            if(shadow)
            {
                SDL_Rect src_rect = {0,0,(Uint16)rendered->w,(Uint16)rendered->h};
                SDL_Rect dst_rect;
                dst_rect = {-1,-1,(Uint16)rendered->w,(Uint16)rendered->h};
                SDL_BlitSurface(shadow, &src_rect, newrendered, &dst_rect);
                dst_rect = {0,-1,(Uint16)rendered->w,(Uint16)rendered->h};
                SDL_BlitSurface(shadow, &src_rect, newrendered, &dst_rect);
                dst_rect = {1,-1,(Uint16)rendered->w,(Uint16)rendered->h};
                SDL_BlitSurface(shadow, &src_rect, newrendered, &dst_rect);
                dst_rect = {-1,0,(Uint16)rendered->w,(Uint16)rendered->h};
                SDL_BlitSurface(shadow, &src_rect, newrendered, &dst_rect);
                dst_rect = {1,0,(Uint16)rendered->w,(Uint16)rendered->h};
                SDL_BlitSurface(shadow, &src_rect, newrendered, &dst_rect);
                dst_rect = {-1,1,(Uint16)rendered->w,(Uint16)rendered->h};
                SDL_BlitSurface(shadow, &src_rect, newrendered, &dst_rect);
                dst_rect = {0,1,(Uint16)rendered->w,(Uint16)rendered->h};
                SDL_BlitSurface(shadow, &src_rect, newrendered, &dst_rect);
                dst_rect = {1,1,(Uint16)rendered->w,(Uint16)rendered->h};
                SDL_BlitSurface(shadow, &src_rect, newrendered, &dst_rect);

                //finally copy inside text
                dst_rect = {0,0,(Uint16)rendered->w,(Uint16)rendered->h};
                SDL_BlitSurface(rendered, &src_rect, newrendered, &dst_rect);

                SyobonKZFreeImage(shadow);
            }
            SyobonKZFreeImage(rendered);
            rendered = newrendered;
        }
    }
    rendered = SyobonKZFixImage(rendered, pstring);
    return rendered;
}

void DrawString(int a, int b, const char *x, Uint32 c)
{
    SDL_Color color;
    SyobonKZGetRGBA(c, color);
    SDL_Surface *rendered = SyobonKZRenderUTF8Text(font[fontsize], x, color);
    if (fontType == DX_FONTTYPE_EDGE)
    {
        SDL_Color blk = {0, 0, 0};
        SDL_Surface *shadow = SyobonKZRenderUTF8Text(font[fontsize], x, blk);
        DrawGraphZ(a - 1, b - 1, shadow);
        DrawGraphZ(a, b - 1, shadow);
        DrawGraphZ(a + 1, b - 1, shadow);
        DrawGraphZ(a - 1, b, shadow);
        DrawGraphZ(a + 1, b, shadow);
        DrawGraphZ(a - 1, b + 1, shadow);
        DrawGraphZ(a, b + 1, shadow);
        DrawGraphZ(a + 1, b + 1, shadow);
        SyobonKZFreeImage(shadow);
    }
    DrawGraphZ(a, b, rendered);
    SyobonKZFreeImage(rendered);
}

void DrawFormatString(int a, int b, Uint32 color, const char *str, ...)
{
    va_list args;
    size_t stringsize = strlen(str) + 16;
    char *newstr = new char[stringsize];
    va_start(args, str);
    vsnprintf(newstr, stringsize, str, args);
    va_end(args);
    DrawString(a, b, newstr, color);
    delete[] newstr;
}

// void DrawFormatString(int a, int b, int c

bool DxLibExit = false;

void SetKeyState(Uint32 key, bool state)
{
    switch (key)
    {
    case KEY_INPUT_0:
        keysHeld.KEY_0 = state;
        break;
    case KEY_INPUT_1:
        keysHeld.KEY_1 = state;
        break;
    case KEY_INPUT_2:
        keysHeld.KEY_2 = state;
        break;
    case KEY_INPUT_3:
        keysHeld.KEY_3 = state;
        break;
    case KEY_INPUT_4:
        keysHeld.KEY_4 = state;
        break;
    case KEY_INPUT_5:
        keysHeld.KEY_5 = state;
        break;
    case KEY_INPUT_6:
        keysHeld.KEY_6 = state;
        break;
    case KEY_INPUT_7:
        keysHeld.KEY_7 = state;
        break;
    case KEY_INPUT_8:
        keysHeld.KEY_8 = state;
        break;
    case KEY_INPUT_9:
        keysHeld.KEY_9 = state;
        break;
    case KEY_INPUT_SPACE:
        keysHeld.KEY_SPACE = state;
        break;
    case KEY_INPUT_RETURN:
        keysHeld.KEY_RETURN = state;
        break;
    case KEY_INPUT_Z:
        keysHeld.KEY_Z = state;
        break;
    case KEY_INPUT_O:
        keysHeld.KEY_O = state;
        break;
    case KEY_INPUT_F1:
        keysHeld.KEY_F1 = state;
        break;
    case KEY_INPUT_UP:
        keysHeld.KEY_UP = state;
        break;
    case KEY_INPUT_DOWN:
        keysHeld.KEY_DOWN = state;
        break;
    case KEY_INPUT_RIGHT:
        keysHeld.KEY_RIGHT = state;
        break;
    case KEY_INPUT_LEFT:
        keysHeld.KEY_LEFT = state;
        break;
    case KEY_INPUT_ESCAPE:
        keysHeld.KEY_ESCAPE = state;
        break;
    case SDLK_SEMICOLON:
        keysHeld.KEY_SEMICOLON = state;
        break;
    default:
        break;
    }
}

bool GetKeyState(Uint32 key)
{
    switch (key)
    {
    case KEY_INPUT_0:
        return keysHeld.KEY_0;
        break;
    case KEY_INPUT_1:
        return keysHeld.KEY_1;
        break;
    case KEY_INPUT_2:
        return keysHeld.KEY_2;
        break;
    case KEY_INPUT_3:
        return keysHeld.KEY_3;
        break;
    case KEY_INPUT_4:
        return keysHeld.KEY_4;
        break;
    case KEY_INPUT_5:
        return keysHeld.KEY_5;
        break;
    case KEY_INPUT_6:
        return keysHeld.KEY_6;
        break;
    case KEY_INPUT_7:
        return keysHeld.KEY_7;
        break;
    case KEY_INPUT_8:
        return keysHeld.KEY_8;
        break;
    case KEY_INPUT_9:
        return keysHeld.KEY_9;
        break;
    case KEY_INPUT_SPACE:
        return keysHeld.KEY_SPACE;
        break;
    case KEY_INPUT_RETURN:
        return keysHeld.KEY_RETURN;
        break;
    case KEY_INPUT_Z:
        return keysHeld.KEY_Z;
        break;
    case KEY_INPUT_O:
        return keysHeld.KEY_O;
        break;
    case KEY_INPUT_F1:
        return keysHeld.KEY_F1;
        break;
    case KEY_INPUT_UP:
        return keysHeld.KEY_UP;
        break;
    case KEY_INPUT_DOWN:
        return keysHeld.KEY_DOWN;
        break;
    case KEY_INPUT_RIGHT:
        return keysHeld.KEY_RIGHT;
        break;
    case KEY_INPUT_LEFT:
        return keysHeld.KEY_LEFT;
        break;
    case KEY_INPUT_ESCAPE:
        return keysHeld.KEY_ESCAPE;
        break;
    case SDLK_SEMICOLON:
        return keysHeld.KEY_SEMICOLON;
        break;
    default:
        return false;
        break;
    }
}

void SyobonKZDrawGraphScaled(int x, int y, int scale_x, int scale_y, SDL_Surface * psurface)
{
    if(psurface)
    {
        SDL_Rect srcrect;
        srcrect.x = srcrect.y = 0;
        srcrect.w = psurface->w * scale_x;
        srcrect.h = psurface->h * scale_y;

        SDL_Rect offset;
        offset.x = x;
        offset.y = y;

        SDL_Surface *flipped = SyobonKZZoomSurface(psurface, scale_x, scale_y, 0);
        SyobonKZSetColorKey(flipped,
                        SYOBON_COLOR_KEY(flipped->format));
        SDL_BlitSurface(flipped, &srcrect, screen, &offset);
        SyobonKZFreeImage(flipped);
    }
}

Uint8 ProcessMessage()
{
    return DxLibExit;
}

Uint8 CheckHitKey(int key)
{
    if (key == KEY_INPUT_Z && GetKeyState(SDLK_SEMICOLON))
        return true;
    return GetKeyState(key);
}

void DrawGraphZ(int a, int b, SDL_Surface *mx)
{
    if (mx)
    {
        SDL_Rect offset;
        offset.x = a;
        offset.y = b;
        SDL_BlitSurface(mx, NULL, screen, &offset);
    }
}

void DrawTurnGraphZ(int a, int b, SDL_Surface *mx)
{
    if (mx)
    {
        SDL_Rect srcrect;
        srcrect.x = srcrect.y = 0;
        srcrect.w = mx->w;
        srcrect.h = mx->h;

        SDL_Rect offset;
        offset.x = a;
        offset.y = b;

        SDL_Surface *flipped = SyobonKZZoomSurface(mx, -1, 1, 0);
        SyobonKZSetColorKey(flipped,
                        SYOBON_COLOR_KEY(flipped->format));
        SDL_BlitSurface(flipped, &srcrect, screen, &offset);
        SyobonKZFreeImage(flipped);
    }
}

void DrawVertTurnGraph(int a, int b, SDL_Surface *mx)
{
    if (mx)
    {
        SDL_Rect srcrect;
        srcrect.x = srcrect.y = 0;
        srcrect.w = mx->w;
        srcrect.h = mx->h;

        SDL_Rect offset;
        offset.x = a - mx->w / 2;
        offset.y = b - mx->h / 2;

        SDL_Surface *flipped = SyobonKZZoomSurface(mx, -1, -1, 0);
        SyobonKZSetColorKey(flipped,
                        SYOBON_COLOR_KEY(flipped->format));
        SDL_BlitSurface(flipped, &srcrect, screen, &offset);
        SyobonKZFreeImage(flipped);
    }
}

SDL_Surface *DerivationGraph(int srcx, int srcy, int width, int height,
                             SDL_Surface *src)
{
    SDL_Surface *img =
        SyobonKZCreateSurface(SDL_SWSURFACE, width, height,
                             screen->format);

    SDL_Rect offset;
    offset.x = srcx;
    offset.y = srcy;
    offset.w = width;
    offset.h = height;

    SDL_BlitSurface(src, &offset, img, NULL);
    SyobonKZSetColorKey(img,
                    SYOBON_COLOR_KEY(img->format));
    return img;
}

// Noticably different than the original
SDL_Surface *LoadGraph(const char *filename, bool fix)
{
    SDL_Surface *image = IMG_Load(filename);

    if (image)
    {
        if (fix)
        {
            image = SyobonKZFixImage(image, filename);
        }

        if (image)
        {
            return image;
        }
    }
    fprintf(stderr, "Error: Unable to load %s: %s\n", filename, SyobonKZGetSDLImgError());
    exit(1);
}

struct ChannelState {
    SyobonKZChunk* sound = nullptr;
    Uint32 StartTime = 0;
};
static ChannelState channels[SYOBONKZ_MIX_CHANNELS];

SyobonKZChunk *GetLastSoundInChannel(int channel)
{
    return channel >= 0 && channel < SYOBONKZ_MIX_CHANNELS ? channels[channel].sound : nullptr;
}

void PlaySoundMem(SyobonKZChunk *s, int l)
{
    if(!sound) //game is muted
        return;

    Uint32 CurrentTime = SDL_GetTicks();

    int bestChannel = -1;

    //dont play if there is the same sound playing in this lapse
    Uint32 Lapse = 30;
    int AllowedInstances = 1;

    //brockbreak.ogg
    if(s == Sounds[3])
    {
        Lapse = 300;
    }

    //coin.ogg
    if(s == Sounds[4])
    {
        Lapse = 250;
        AllowedInstances = 2;
    }

    // Try to find free channel
    for (int i = 0; i < SYOBONKZ_MIX_CHANNELS; i++)
    {
        if (!SyobonKZIsChannelPlaying(i))
        {
            bestChannel = i;
        }
 
        if (channels[i].sound == s)
        {
            if(CurrentTime < channels[i].StartTime + Lapse)
            {
                //Same sound already just started playing, dont overlap
                //but check for allowed instances first
                AllowedInstances--;
                if(!AllowedInstances)
                    return;
                else
                    continue;
            }

            bestChannel = i;
            break;
        }
    }
    

    if (bestChannel == -1)
        return;

    SyobonKZHaltChannel(bestChannel);
    SyobonKZPlayChunk(bestChannel, s, l);

    channels[bestChannel].sound = s;
    channels[bestChannel].StartTime = CurrentTime;
}

SyobonKZChunk *LoadSoundMem(const char *f)
{
    if (!sound)
        return NULL;

    SyobonKZChunk *s = SyobonKZLoadChunk(f);
    if (s)
        return s;
    fprintf(stderr, "Error: Unable to load sound %s: %s\n", f, SyobonKZGetSDLMixError());
    return NULL;
}

SyobonKZMusic *LoadMusicMem(const char *f)
{
    if (!sound)
        return NULL;

    SyobonKZMusic *m = SyobonKZLoadMusic(f);
    if (m)
        return m;
    fprintf(stderr, "Error: Unable to load music %s: %s\n", f, SyobonKZGetSDLMixError());
    return NULL;
}
