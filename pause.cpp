#include "sdl_includer.h"
#include "global_vars.h"
#include "main.h"
#include "pause.h"
#include "title.h"
#include "config.h"

const char *pPauseLabels[] = {
    "Resume",
    "Options",
    "Title screen",
    "Quit",
    nullptr,
};

const char *pTitleLabels[] = {
    "Resume",
    "Options",
    "Quit",
    nullptr,
};

const char *pOptionsLabels[] = {
    "Toggle fullscreen",
    "Save changes",
    nullptr,
};

int Offset = 0;
int CurrentSelection = 0;
bool Selected = false;
bool PauseMenuKeyPressed = false;

static ESyobonState prevSyobonState = (ESyobonState)-1;

#define PAUSE_MAX_RENDER_OPTIONS 6

EPauseState PauseState = EPauseState::PAUSE;

void HandlePauseKeys()
{
    if(CheckHitKey(KEY_INPUT_UP))
    {
        if(!PauseMenuKeyPressed)
        {
            CurrentSelection--;
            if(CurrentSelection < 0)
            {
                CurrentSelection = 0;
                const char ** pcurrent_labels = GetCurrentLabels();
                if(pcurrent_labels)
                {
                    while(pcurrent_labels[CurrentSelection])
                    {
                        CurrentSelection++;
                    }
                    if(CurrentSelection > 0)
                        CurrentSelection--;
                }
            }
        }
        PauseMenuKeyPressed = true;
    }
    else if(CheckHitKey(KEY_INPUT_DOWN))
    {
        if(!PauseMenuKeyPressed)
        {
            CurrentSelection++;
            const char ** pcurrent_labels = GetCurrentLabels();
            if(!pcurrent_labels || (pcurrent_labels && !pcurrent_labels[CurrentSelection]))
            {
                CurrentSelection = 0;
            }
        }
        PauseMenuKeyPressed = true;
    }
    else if(CheckHitKey(KEY_INPUT_Z) || CheckHitKey(KEY_INPUT_RETURN))
    {
        if(!PauseMenuKeyPressed)
            Selected = true;
        else
            Selected = false;
        PauseMenuKeyPressed = true;
    }
    else
    {
        Selected = false;
        PauseMenuKeyPressed = false;
    }
}

const char ** GetCurrentLabels()
{
    if(PauseState == EPauseState::PAUSE)
    {
        if(prevSyobonState == ESyobonState::TITLE)
            return pTitleLabels;
        else
            return pPauseLabels;
    }
    else if(PauseState == EPauseState::OPTIONS)
    {
        return pOptionsLabels;
    }
    return nullptr;
}

int GetCurrentMaxRenderOptions()
{
    //for now just PAUSE_MAX_RENDER_OPTIONS
    return PAUSE_MAX_RENDER_OPTIONS;
}

void TogglePauseState(EPauseState state)
{
    if(SyobonState != ESyobonState::PAUSE)
    {
        prevSyobonState = SyobonState;
        SyobonState = ESyobonState::PAUSE;
        PauseState = state;
        CurrentSelection = 0;
    }
    else
    {
        SyobonState = prevSyobonState;
    }
}

void HandlePauseState()
{
    HandlePauseKeys();

    if(Selected)
    {

        #define SELECTED_LABEL(text) (!strncmp(pcurrent_labels[CurrentSelection], text, sizeof(text)))

        const char ** pcurrent_labels = GetCurrentLabels();
        if(pcurrent_labels && pcurrent_labels[CurrentSelection])
        {
            if(PauseState == EPauseState::PAUSE)
            {
                if(SELECTED_LABEL("Quit"))
                {
                    SyobonQuit = 3;
                }
                else if(SELECTED_LABEL("Resume") || SELECTED_LABEL("Save changes"))
                {
                    if(SELECTED_LABEL("Save changes"))
                        SaveConfig();
                    TogglePauseState(EPauseState::PAUSE);
                    TitleWaitToReleaseKey();
                }
                else if(SELECTED_LABEL("Title screen"))
                {
                    TogglePauseState(EPauseState::PAUSE);
                    GoToTitleScreen();
                    TitleWaitToReleaseKey();
                }
                else if(SELECTED_LABEL("Options"))
                {
                    PauseState = EPauseState::OPTIONS;
                }
            }
            else if(PauseState == EPauseState::OPTIONS)
            {
                if(SELECTED_LABEL("Return") || SELECTED_LABEL("Save changes"))
                {
                    if(SELECTED_LABEL("Save changes"))
                        SaveConfig();
                    PauseState = EPauseState::PAUSE;
                }
                else if(SELECTED_LABEL("Toggle fullscreen"))
                {
                    SyobonKZToggleFullscreen();
                }
            }
        }
    }
}

void RenderPauseState()
{
    SyobonKZFillRect(screen, 0, 0);
    setc1();

    DrawString(480 / 2 - ((sizeof("Paused") - 1) * 9) / 2, 50, "Paused", color);

    const char ** pcurrent_labels = GetCurrentLabels();
    if(pcurrent_labels)
    {
        for(int i = Offset; i < Offset + GetCurrentMaxRenderOptions(); i++)
        {
            if(!pcurrent_labels[i]) // nullptr
                break;

            if(!pcurrent_labels[i][0]) // '\0'
                continue;

            DrawString(480 / 2 - (strlen(pcurrent_labels[i]) * 9) / 2, 100 + (i * 30), pcurrent_labels[i], color);
            if(CurrentSelection == i)
            {
                DrawString(480 / 2 - ((strlen(pcurrent_labels[i]) + 5) * 9) / 2, 100 + (i * 30), "->", color);
                DrawString(480 / 2 + ((strlen(pcurrent_labels[i])) * 9) / 2, 100 + (i * 30), "<-", color);
            }
        }
    }
}
