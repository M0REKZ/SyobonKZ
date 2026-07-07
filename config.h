#ifndef SYOBON_CONFIG_H
#define SYOBON_CONFIG_H

#include <set>
#include "global_vars.h"

//+KZ: for config and save data

void SaveConfig();
void LoadConfig();

struct SSyobonGameLevel
{
    ESyobonActionGame Game;
    int World;
    int Level;

    inline bool operator==(const SSyobonGameLevel& other) const
    {
        return (
            this->Game == other.Game &&
            this->World == other.World &&
            this->Level == other.Level
        );
    }

    inline bool operator<(const SSyobonGameLevel& other) const
    {
        return (
            this->Game < other.Game ||
            this->World < other.World ||
            this->Level < other.Level
        );
    }
};

struct SConfig
{
    std::set<SSyobonGameLevel> LevelsFinished;
    int Fullscreen = false;
};

extern SConfig SyobonGlobalConfig;


#endif
