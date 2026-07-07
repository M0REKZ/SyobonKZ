#include "config.h"
#include "crossplatform.h"

#include <fstream>

SConfig SyobonGlobalConfig;

void SaveConfig()
{
    const char * psave_dir = GetSavePath();

    if(psave_dir)
    {
        char filepath[256] = {0};
        snprintf(filepath, sizeof(filepath), "%s/save.txt", GetSavePath());
        std::ofstream file(filepath);

        for(auto &LevelFinished : SyobonGlobalConfig.LevelsFinished)
        {
            file << "LEVEL_FINISHED " << (int)LevelFinished.Game <<  " " << LevelFinished.World <<  " " << LevelFinished.Level << std::endl;
            file << "FULLSCREEN " << (int)SyobonKZIsFullscreen() << std::endl;
        }

        file.close();
    }
}

void LoadConfig()
{
    SyobonGlobalConfig.LevelsFinished.clear();

    const char * psave_dir = GetSavePath();

    if(psave_dir)
    {
        char filepath[256] = {0};
        snprintf(filepath, sizeof(filepath), "%s/save.txt", psave_dir);
        std::ifstream file(filepath);

        std::string line;

        while(std::getline(file, line))
        {
            if(strstr(line.c_str(), "LEVEL_FINISHED"))
            {
                SSyobonGameLevel temp;
                int game;
                sscanf(line.c_str(), "LEVEL_FINISHED %d %d %d", &game, &temp.World, &temp.Level);
                temp.Game = (ESyobonActionGame)game;
                SyobonGlobalConfig.LevelsFinished.push_back(temp);
            }
            if(strstr(line.c_str(), "FULLSCREEN"))
            {
                sscanf(line.c_str(), "FULLSCREEN %d", &SyobonGlobalConfig.Fullscreen);
            }
        }

        file.close();
    }
}
