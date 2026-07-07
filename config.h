#ifndef SYOBON_CONFIG_H
#define SYOBON_CONFIG_H

#include <vector>
#include "global_vars.h"

//+KZ: for config and save data

void SaveConfig();
void LoadConfig();

struct SSyobonGameLevel
{
    ESyobonActionGame Game;
    int World;
    int Level;
};

struct SConfig
{
    std::vector<SSyobonGameLevel> LevelsFinished;
    int Fullscreen = false;
};

extern SConfig SyobonGlobalConfig;


#endif
