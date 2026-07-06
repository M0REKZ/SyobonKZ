#ifndef SYOBON_PAUSE_H
#define SYOBON_PAUSE_H

enum class EPauseState : int
{
    PAUSE = 0,
    OPTIONS,
};

void HandlePauseKeys();

const char ** GetCurrentLabels();
int GetCurrentMaxRenderOptions();

void TogglePauseState(EPauseState state);

void HandlePauseState();
void RenderPauseState();

#endif
