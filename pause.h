#ifndef SYOBON_PAUSE_H
#define SYOBON_PAUSE_H

enum class EPauseState : int
{
    PAUSE = 0,
    OPTIONS,
    LEVEL_SELECT,
};

void HandlePauseKeys();

void AdjustOffset();
void ResetSelection();

const char ** GetCurrentLabels();
int GetCurrentMaxRenderOptions();

void TogglePauseState(EPauseState state);
void ChangeToPauseState(EPauseState newstate);

void HandlePauseState();
void RenderPauseState();

#endif
