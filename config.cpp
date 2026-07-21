#include "config.h"
#include "crossplatform.h"

#include <fstream>

SConfig SyobonGlobalConfig;

#ifdef __EMSCRIPTEN__
    EM_JS(void, InitSaveFS, (const char* savepath), {
        const mountPath = UTF8ToString(savepath);

        Asyncify.handleSleep(function(wakeUp) {
            try {
                FS.mkdir(mountPath);
            } catch (e) {}

            try {
                FS.mount(IDBFS, {}, mountPath);
            } catch (e) {}

            FS.syncfs(true, function(err) {
                if (err)
                    console.error(err);

                wakeUp();
            });
        });
    });

    EM_JS(void, FlushSaveFS, (), {
        FS.syncfs(false, function(err) {
            if (err)
                console.error(err);
        });
    });  
#endif

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
        }
        file << "FULLSCREEN " << (int)SyobonKZIsFullscreen() << std::endl;

        file.close();

        #ifdef __EMSCRIPTEN__
            FlushSaveFS();
        #endif
    }
}

void LoadConfig()
{
    #ifdef __EMSCRIPTEN__
        InitSaveFS(SYOBONKZ_EMSCRIPTEN_SAVEPATH);
    #endif

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
                SyobonGlobalConfig.LevelsFinished.insert(temp);
            }
            if(strstr(line.c_str(), "FULLSCREEN"))
            {
                sscanf(line.c_str(), "FULLSCREEN %d", &SyobonGlobalConfig.Fullscreen);
            }
        }

        file.close();
    }
}
