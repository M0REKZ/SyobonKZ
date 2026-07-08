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

const char *pLevelSelectSA_1_AND_2[] = {
    "Level 1-1",
    "Level 1-2",
    "Level 1-3",
    "Level 1-4",
    "Level 2-1",
    "Level 2-2",
    "Level 2-3",
    "Level 2-4",
    "Special Level 9",
    nullptr,
};

const char *pLevelSelectSA_3[] = {
    "Level 1",
    "Level 2",
    "Level 3",
    "Level 4",
    "Level 5",
    nullptr,
};

const char *pLevelSelectKaizoSyobon[] = {
    "Level 1",
    "Level 2",
    "Level 3",
    "Level 4",
    nullptr,
};


bool OptionsAvailable[] = {
    true,
    true,
    true,
    true,
    true,
    true,
    true,
    true,
    true,
    true,
    true,
    true,
    true,
    true,
    true,
    true,
    true,
    true,
    true,
    true,
};

bool ShowLevelAsFinished[] = {
    true,
    true,
    true,
    true,
    true,
    true,
    true,
    true,
    true,
    true,
    true,
    true,
    true,
    true,
    true,
    true,
    true,
    true,
    true,
    true,
};

int Offset = 0;
int CurrentSelection = 0;
bool Selected = false;
bool PauseMenuKeyPressed = false;

static ESyobonGameState prevSyobonState = (ESyobonGameState)-1;

#define PAUSE_MAX_RENDER_OPTIONS 12
#define LEVEL_SELECT_MAX_RENDER_OPTIONS 6

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
            AdjustOffset();
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
            AdjustOffset();
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

void AdjustOffset()
{
    if(CurrentSelection < Offset)
    {
        Offset = CurrentSelection;
    }
    else if(CurrentSelection >= Offset + GetCurrentMaxRenderOptions())
    {
        Offset = CurrentSelection - (GetCurrentMaxRenderOptions() - 1);
    }
}

void ResetSelection()
{
    Selected = false;
    CurrentSelection = 0;
    Offset = 0;
}

const char ** GetCurrentLabels()
{
    if(PauseState == EPauseState::PAUSE)
    {
        if(prevSyobonState == ESyobonGameState::TITLE)
            return pTitleLabels;
        else
            return pPauseLabels;
    }
    else if(PauseState == EPauseState::OPTIONS)
    {
        return pOptionsLabels;
    }
    else if(PauseState == EPauseState::LEVEL_SELECT)
    {
        switch (currentGame)
        {
        case ESyobonActionGame::SYOBON_ACTION_1_AND_2:
            return pLevelSelectSA_1_AND_2;
            break;
        case ESyobonActionGame::SYOBON_ACTION_3:
            return pLevelSelectSA_3;
            break;
        case ESyobonActionGame::KAIZO_SYOBON:
            return pLevelSelectKaizoSyobon;
            break;
        }
    }
    return nullptr;
}

int GetCurrentMaxRenderOptions()
{
    //for now just PAUSE_MAX_RENDER_OPTIONS
    if(PauseState == EPauseState::LEVEL_SELECT)
        return LEVEL_SELECT_MAX_RENDER_OPTIONS;
    return PAUSE_MAX_RENDER_OPTIONS;
}

void TogglePauseState(EPauseState state)
{
    if(SyobonState != ESyobonGameState::PAUSE)
    {
        prevSyobonState = SyobonState;
        SyobonState = ESyobonGameState::PAUSE;
        PauseMenuKeyPressed = true;
        ChangeToPauseState(state);
    }
    else
    {
        SyobonState = prevSyobonState;
    }
}

void ChangeToPauseState(EPauseState newstate)
{
    PauseState = newstate;
    ResetSelection();

    switch (newstate)
    {
    case EPauseState::LEVEL_SELECT:
        for(auto &showasfinished : ShowLevelAsFinished)
        {
            showasfinished = false;
        }
        for(auto &optionavailable : OptionsAvailable)
        {
            optionavailable = false;
        }

        //level 1 is always available
        OptionsAvailable[0] = true;
        OptionsAvailable[8] = currentGame == ESyobonActionGame::SYOBON_ACTION_1_AND_2 ? true : false;

        //check for finished levels
        for(auto finishedlevel : SyobonGlobalConfig.LevelsFinished)
        {
            if(finishedlevel.Game != currentGame)
                continue;
            
            switch (currentGame)
            {
            case ESyobonActionGame::SYOBON_ACTION_1_AND_2:
            
                //Syobon Action 1
                for(int lvl = 1; lvl < 5; lvl++)
                {
                    if(finishedlevel.World == 1 && finishedlevel.Level == lvl)
                    {
                        OptionsAvailable[lvl] = true;
                        ShowLevelAsFinished[lvl - 1] = true;
                    }
                }

                //Syobon Action 2
                for(int lvl = 1; lvl < 4; lvl++)
                {
                    if(finishedlevel.World == 2 && finishedlevel.Level == lvl)
                    {
                        OptionsAvailable[lvl + 4] = true;
                        ShowLevelAsFinished[lvl + 3] = true;
                    }
                }

                // Syobon Action 2 level 9
                if(finishedlevel.World == 3 && finishedlevel.Level == 1)
                {
                    OptionsAvailable[8] = true;
                    ShowLevelAsFinished[8] = true;
                }
                break;
            
            case ESyobonActionGame::SYOBON_ACTION_3:
                for(int lvl = 1; lvl < 6; lvl++)
                {
                    if(finishedlevel.World == 1 && finishedlevel.Level == lvl)
                    {
                        OptionsAvailable[lvl] = true;
                        ShowLevelAsFinished[lvl - 1] = true;
                    }
                }
                break;
            case ESyobonActionGame::KAIZO_SYOBON:
                for(int lvl = 1; lvl < 5; lvl++)
                {
                    if(finishedlevel.World == 1 && finishedlevel.Level == lvl)
                    {
                        OptionsAvailable[lvl] = true;
                        ShowLevelAsFinished[lvl - 1] = true;
                    }
                }
                break;
            }
        }

        break;
    
    default:
        for(auto &optionavailable : OptionsAvailable)
        {
            optionavailable = true;
        }
        break;
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
                    ResetSelection();
                }
            }
            else if(PauseState == EPauseState::OPTIONS)
            {
                if(SELECTED_LABEL("Return") || SELECTED_LABEL("Save changes"))
                {
                    if(SELECTED_LABEL("Save changes"))
                        SaveConfig();
                    PauseState = EPauseState::PAUSE;
                    ResetSelection();
                }
                else if(SELECTED_LABEL("Toggle fullscreen"))
                {
                    SyobonKZToggleFullscreen();
                }
            }
            else if(PauseState == EPauseState::LEVEL_SELECT)
            {
                bool startgame = false;

                if(OptionsAvailable[CurrentSelection])
                {
                    //get level from selection
                    switch(currentGame)
                    {
                    case ESyobonActionGame::SYOBON_ACTION_1_AND_2:
                        if(CurrentSelection >= 0 && CurrentSelection < 4)
                        {
                            SyobonWorld = 1;
                            SyobonLevel = CurrentSelection + 1;
                            SyobonSection = 0;
                        }
                        else if(CurrentSelection >= 4 && CurrentSelection < 8)
                        {
                            SyobonWorld = 2;
                            SyobonLevel = CurrentSelection - 3;
                            SyobonSection = 0;
                        }
                        else if(CurrentSelection == 8)
                        {
                            SyobonWorld = 3;
                            SyobonLevel = 1;
                            SyobonSection = 0;
                        }
                        break;
                    case ESyobonActionGame::SYOBON_ACTION_3:
                        if(CurrentSelection >= 0 && CurrentSelection < 5)
                        {
                            SyobonWorld = 1;
                            SyobonLevel = CurrentSelection + 1;
                            SyobonSection = 0;
                        }
                        break;
                    case ESyobonActionGame::KAIZO_SYOBON:
                        if(CurrentSelection >= 0 && CurrentSelection < 4)
                        {
                            SyobonWorld = 1;
                            SyobonLevel = CurrentSelection + 1;
                            SyobonSection = 0;
                        }
                        break;
                    }

                    startgame = true;
                }

                if(startgame)
                {
                    SyobonStartGame = true;
                    TogglePauseState(EPauseState::PAUSE);
                    TitleWaitToReleaseKey();
                }
            }
        }
    }
}

void RenderPauseState()
{
    SyobonKZFillRect(screen, 0, 0);
    setc1();

    if(PauseState == EPauseState::LEVEL_SELECT)
        DrawString(480 / 2 - ((sizeof("Select level:") - 1) * 9) / 2, 30, "Select level:", color);
    else
        DrawString(480 / 2 - ((sizeof("Paused") - 1) * 9) / 2, 50, "Paused", color);

    const char ** pcurrent_labels = GetCurrentLabels();
    if(pcurrent_labels)
    {
        int optionYsize = 30;

        if(PauseState == EPauseState::LEVEL_SELECT)
            optionYsize = 50;

        if(Offset)
            DrawString(480 / 2 - (9) / 2, 100 - (optionYsize - 5), "Λ", color);

        bool drawdownarrow = true;
        for(int i = Offset; i < Offset + GetCurrentMaxRenderOptions(); i++)
        {
            if(!pcurrent_labels[i]) // nullptr
            {
                drawdownarrow = false;
                break;
            }

            if(!pcurrent_labels[i][0]) // '\0'
                continue;

            if(!OptionsAvailable[i])
            {
                setcolor(100,100,100);
            }
            else
            {
                setc1();
            }

            int ypos = i - Offset;

            DrawString(480 / 2 - (strlen(pcurrent_labels[i]) * 9) / 2, 100 + (ypos * optionYsize), pcurrent_labels[i], color);
            if(PauseState == EPauseState::LEVEL_SELECT)
            {
                int x = -10;
                int y = (100 - optionYsize / 3) + (ypos * optionYsize);
                if(CurrentSelection == i)
                    SyobonKZRectangleColor(screen, x, y, x + 500, y + optionYsize, color);

                SDL_Surface * psurf = Sliced_GFX_KZ[4];
                if(ShowLevelAsFinished[i])
                    psurf = Sliced_GFX_KZ[2];
                else if(OptionsAvailable[i])
                    psurf = Sliced_GFX_KZ[3];

                SyobonKZDrawGraphScaled(30, y + (optionYsize/2 - psurf->h), 2, 2, psurf);
            }
            else
            {
                if(CurrentSelection == i)
                {
                    DrawString(480 / 2 - ((strlen(pcurrent_labels[i]) + 5) * 9) / 2, 100 + (ypos * optionYsize), "->", color);
                    DrawString(480 / 2 + ((strlen(pcurrent_labels[i])) * 9) / 2, 100 + (ypos * optionYsize), "<-", color);
                }
            }
        }
        if(drawdownarrow && pcurrent_labels[(Offset + GetCurrentMaxRenderOptions())])
            DrawString(480 / 2 - (9) / 2, 100 + (GetCurrentMaxRenderOptions() * optionYsize - 5), "V", color);
    }
}
