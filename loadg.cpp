#include "DxLib.h"
#include "global_vars.h"
#include "main.h"

int x1;


void loadg(void)
{

    for (t = 0; t < 51; t++)
    {
        Main_GFX[t] = 0;
    }
    for (int i = 0; i < 161; i++)
        for (int j = 0; j < 8; j++)
            Sliced_GFX[i][j] = NULL;

    /*
    for (t=0;t<161;t++){
    for (tt=0;tt<8;tt++){
    Sliced_GFX[t][tt]=0;
    }}
    */

    // ma-=100;//mb==5000;
    // end();

    // 画像読み込み

    // 透過色を変更
    // SetTransColor( 9*16+9 , 255 , 255 ) ;

    //+KZ: the first image should have the format that every other image should use
    // ブロック (Block)
    Main_GFX[1] = LoadGraph("res/brock.png");
    // アイテム (item)
    Main_GFX[2] = LoadGraph("res/item.png");
    // 敵 (enemy)
    Main_GFX[3] = LoadGraph("res/teki.png");
    // 背景 (background)
    Main_GFX[4] = LoadGraph("res/haikei.png");
    // ブロック2 (Block 2)
    Main_GFX[5] = LoadGraph("res/brock2.png");
    // おまけ (Extra)
    Main_GFX[6] = LoadGraph("res/omake.png");
    // おまけ2 (Extra 2)
    Main_GFX[7] = LoadGraph("res/omake2.png");
    // タイトル (Title)
    Main_GFX[30] = LoadGraph("res/syobon3.png", false);
    // プレイヤー (Player)
    Main_GFX[0] = LoadGraph("res/player.png");

    // Added by +KZ:
    Main_GFX_KZ[0] = LoadGraph("res/decoration_kz.png");
    Main_GFX_KZ[1] = LoadGraph("res/sa3/title.png", false);
    Main_GFX_KZ[2] = LoadGraph("res/sa3/spike.png", false);

    Sliced_GFX_KZ[0] = DerivationGraph(0, 0, 64, 29, Main_GFX_KZ[0]);
    Sliced_GFX_KZ[1] = DerivationGraph(0, 31, 70, 40, Main_GFX_KZ[0]);

    // プレイヤー読み込み (Player loading)
    Sliced_GFX[40][0] = DerivationGraph(0, 0, 30, 36, Main_GFX[0]);
    Sliced_GFX[0][0] = DerivationGraph(31 * 4, 0, 30, 36, Main_GFX[0]);
    Sliced_GFX[1][0] = DerivationGraph(31 * 1, 0, 30, 36, Main_GFX[0]);
    Sliced_GFX[2][0] = DerivationGraph(31 * 2, 0, 30, 36, Main_GFX[0]);
    Sliced_GFX[3][0] = DerivationGraph(31 * 3, 0, 30, 36, Main_GFX[0]);
    Sliced_GFX[41][0] = DerivationGraph(50, 0, 51, 73, Main_GFX[6]);

    x1 = 1;
    // ブロック読み込み (Block loading)
    for (t = 0; t <= 6; t++)
    {
        Sliced_GFX[t][x1] = DerivationGraph(33 * t, 0, 30, 30, Main_GFX[x1]);
        Sliced_GFX[t + 30][x1] = DerivationGraph(33 * t, 33, 30, 30, Main_GFX[x1]);
        Sliced_GFX[t + 60][x1] = DerivationGraph(33 * t, 66, 30, 30, Main_GFX[x1]);
        Sliced_GFX[t + 90][x1] = DerivationGraph(33 * t, 99, 30, 30, Main_GFX[x1]);
    }
    Sliced_GFX[8][x1] = DerivationGraph(33 * 7, 0, 30, 30, Main_GFX[x1]);
    Sliced_GFX[16][x1] = DerivationGraph(33 * 6, 0, 24, 27, Main_GFX[2]);
    Sliced_GFX[10][x1] = DerivationGraph(33 * 9, 0, 30, 30, Main_GFX[x1]);
    Sliced_GFX[40][x1] = DerivationGraph(33 * 9, 33, 30, 30, Main_GFX[x1]);
    Sliced_GFX[70][x1] = DerivationGraph(33 * 9, 66, 30, 30, Main_GFX[x1]);
    Sliced_GFX[100][x1] = DerivationGraph(33 * 9, 99, 30, 30, Main_GFX[x1]);
    // ブロック読み込み2 (Block loading 2)
    x1 = 5;
    for (t = 0; t <= 6; t++)
    {
        Sliced_GFX[t][x1] = DerivationGraph(33 * t, 0, 30, 30, Main_GFX[x1]);
    }
    Sliced_GFX[10][5] = DerivationGraph(33 * 1, 33, 30, 30, Main_GFX[x1]);
    Sliced_GFX[11][5] = DerivationGraph(33 * 2, 33, 30, 30, Main_GFX[x1]);
    Sliced_GFX[12][5] = DerivationGraph(33 * 0, 66, 30, 30, Main_GFX[x1]);
    Sliced_GFX[13][5] = DerivationGraph(33 * 1, 66, 30, 30, Main_GFX[x1]);
    Sliced_GFX[14][5] = DerivationGraph(33 * 2, 66, 30, 30, Main_GFX[x1]);

    // アイテム読み込み (Item loading)
    x1 = 2;
    for (t = 0; t <= 5; t++)
    {
        Sliced_GFX[t][x1] = DerivationGraph(33 * t, 0, 30, 30, Main_GFX[x1]);
    }

    // 敵キャラ読み込み (Loading enemy characters)
    x1 = 3;
    Sliced_GFX[0][x1] = DerivationGraph(33 * 0, 0, 30, 30, Main_GFX[x1]);
    Sliced_GFX[1][x1] = DerivationGraph(33 * 1, 0, 30, 43, Main_GFX[x1]);
    Sliced_GFX[2][x1] = DerivationGraph(33 * 2, 0, 30, 30, Main_GFX[x1]);
    Sliced_GFX[3][x1] = DerivationGraph(33 * 3, 0, 30, 44, Main_GFX[x1]);
    Sliced_GFX[4][x1] = DerivationGraph(33 * 4, 0, 33, 35, Main_GFX[x1]);
    Sliced_GFX[5][x1] = DerivationGraph(0, 0, 37, 55, Main_GFX[7]);
    Sliced_GFX[6][x1] = DerivationGraph(38 * 2, 0, 36, 50, Main_GFX[7]);
    Sliced_GFX[150][x1] = DerivationGraph(38 * 2 + 37 * 2, 0, 36, 50, Main_GFX[7]);
    Sliced_GFX[7][x1] = DerivationGraph(33 * 6 + 1, 0, 32, 32, Main_GFX[x1]);
    Sliced_GFX[8][x1] = DerivationGraph(38 * 2 + 37 * 3, 0, 37, 47, Main_GFX[7]);
    Sliced_GFX[151][x1] = DerivationGraph(38 * 3 + 37 * 3, 0, 37, 47, Main_GFX[7]);
    Sliced_GFX[9][x1] = DerivationGraph(33 * 7 + 1, 0, 26, 30, Main_GFX[x1]);
    Sliced_GFX[10][x1] = DerivationGraph(214, 0, 46, 16, Main_GFX[6]);

    // モララー (Molalla)
    Sliced_GFX[30][x1] = DerivationGraph(0, 56, 30, 36, Main_GFX[7]);
    Sliced_GFX[155][x1] = DerivationGraph(31 * 3, 56, 30, 36, Main_GFX[7]);
    Sliced_GFX[31][x1] = DerivationGraph(50, 74, 49, 79, Main_GFX[6]);

    Sliced_GFX[80][x1] = DerivationGraph(151, 31, 70, 40, Main_GFX[4]);
    Sliced_GFX[81][x1] = DerivationGraph(151, 72, 70, 40, Main_GFX[4]);
    Sliced_GFX[130][x1] = DerivationGraph(151 + 71, 72, 70, 40, Main_GFX[4]);
    Sliced_GFX[82][x1] = DerivationGraph(33 * 1, 0, 30, 30, Main_GFX[5]);
    Sliced_GFX[83][x1] = DerivationGraph(0, 0, 49, 48, Main_GFX[6]);
    Sliced_GFX[84][x1] = DerivationGraph(33 * 5 + 1, 0, 30, 30, Main_GFX[x1]);
    Sliced_GFX[86][x1] = DerivationGraph(102, 66, 49, 59, Main_GFX[6]);
    Sliced_GFX[152][x1] = DerivationGraph(152, 66, 49, 59, Main_GFX[6]);

    Sliced_GFX[90][x1] = DerivationGraph(102, 0, 64, 63, Main_GFX[6]);

    Sliced_GFX[100][x1] = DerivationGraph(33 * 1, 0, 30, 30, Main_GFX[2]);
    Sliced_GFX[101][x1] = DerivationGraph(33 * 7, 0, 30, 30, Main_GFX[2]);
    Sliced_GFX[102][x1] = DerivationGraph(33 * 3, 0, 30, 30, Main_GFX[2]);

    // Sliced_GFX[104][x1] = DerivationGraph( 33*2, 0, 30, 30, Main_GFX[5]) ;
    Sliced_GFX[105][x1] = DerivationGraph(33 * 5, 0, 30, 30, Main_GFX[2]);
    Sliced_GFX[110][x1] = DerivationGraph(33 * 4, 0, 30, 30, Main_GFX[2]);

    // 背景読み込み (Background loading)
    x1 = 4;
    Sliced_GFX[0][x1] = DerivationGraph(0, 0, 150, 90, Main_GFX[x1]);
    Sliced_GFX[1][x1] = DerivationGraph(151, 0, 65, 29, Main_GFX[x1]);
    Sliced_GFX[2][x1] = DerivationGraph(151, 31, 70, 40, Main_GFX[x1]);
    Sliced_GFX[3][x1] = DerivationGraph(0, 91, 100, 90, Main_GFX[x1]);
    Sliced_GFX[4][x1] = DerivationGraph(151, 113, 51, 29, Main_GFX[x1]);
    Sliced_GFX[5][x1] = DerivationGraph(222, 0, 28, 60, Main_GFX[x1]);
    Sliced_GFX[6][x1] = DerivationGraph(151, 143, 90, 40, Main_GFX[x1]);
    Sliced_GFX[30][x1] = DerivationGraph(293, 0, 149, 90, Main_GFX[x1]);

    //+KZ: Sliced_GFX[31][4] is 3-1 grass?? 3-1 also wants a Sliced_GFX[32][4] sprite, which seems to be a cloud
    // sadly there is not a official Syobon Action 2 release containing the missing sprites.
    // Sliced_GFX[32][4] was not even in this list, so probably the creator of that mod
    // forgot to upload loadg.cpp and the assets in the latest game zip...
    // im using alternative edited versions for now
    Sliced_GFX[31][x1] = Sliced_GFX_KZ[0]; // DerivationGraph(293, 92, 64, 29, Main_GFX[x1]);
    Sliced_GFX[32][x1] = Sliced_GFX_KZ[1];

    // 中間フラグ (Intermediate flag)
    //+KZ: 42 to fix gray line, previously it was 40
    //Original Syobon Action had it in 0, i prefer the version with text
    Sliced_GFX[20][x1] = DerivationGraph(42, 182, 40, 60, Main_GFX[x1]);

    // グラ
    x1 = 5;
    Sliced_GFX[0][x1] = DerivationGraph(167, 0, 45, 45, Main_GFX[6]);

    // 敵サイズ収得
    // int GrHandle=0;
    x1 = 3;
    for (t = 0; t <= 140; t++)
    {
        if (Sliced_GFX[t][x1])
        {
            EnemyDefaultSizeX[t] = Sliced_GFX[t][x1]->w;
            EnemyDefaultSizeY[t] = Sliced_GFX[t][x1]->h;
            // GetGraphSize(Sliced_GFX[t][x1] ,&anx[t] ,&any[t]);
            EnemyDefaultSizeX[t] *= 100;
            EnemyDefaultSizeY[t] *= 100;
        }
        else
        {
            EnemyDefaultSizeX[t] = 0;
            EnemyDefaultSizeY[t] = 0;
        }
    }
    EnemyDefaultSizeX[79] = 120 * 100;
    EnemyDefaultSizeY[79] = 15 * 100;
    EnemyDefaultSizeX[85] = 25 * 100;
    EnemyDefaultSizeY[85] = 30 * 10 * 100;

    // 背景サイズ収得 (Background size acquisition)
    x1 = 4;
    //+KZ: value is set but never used
    /*for (t = 0; t < 40; t++)
    {
        if (Sliced_GFX[t][x1])
        {
            BackgroundWidth[t] = Sliced_GFX[t][x1]->w;
            BackgroundHeight[t] = Sliced_GFX[t][x1]->h;
            // GetGraphSize(Sliced_GFX[t][x1] ,&ne[t] ,&nf[t]);
            // ne[t]*=100;nf[t]*=100;
        }
        else
        {
            BackgroundWidth[t] = 0;
            BackgroundHeight[t] = 0;
        }
    }*/

    /*
    anx[0]=30;any[0]=30;
    anx[1]=30;any[1]=43;
    anx[2]=30;any[2]=30;
    anx[3]=30;any[3]=44;
    */

    // ogg読み込み
    // try{
    // Sounds[2] = LoadSoundMem( "SE/1.mp3" ) ;
    Music[1] = LoadMusicMem("BGM/field.ogg");   // 50
    Music[2] = LoadMusicMem("BGM/dungeon.ogg"); // 40
    Music[3] = LoadMusicMem("BGM/star4.ogg");   // 50
    Music[4] = LoadMusicMem("BGM/castle.ogg");  // 50
    Music[5] = LoadMusicMem("BGM/puyo.ogg");    // 50
    Music[6] = LoadMusicMem("BGM/field3.mp3");  //+KZ from Syobon Action 2 (English version)
                                               // Music[6]=LoadMusicMem( "BGM/last.ogg");
    // ChangeVolumeSoundMem(50, Music[6]);

    Sounds[1] = LoadSoundMem("SE/jump.ogg");
    // Sounds[2] = LoadSoundMem("SE/brockcoin.ogg");
    Sounds[3] = LoadSoundMem("SE/brockbreak.ogg");
    Sounds[4] = LoadSoundMem("SE/coin.ogg");
    Sounds[5] = LoadSoundMem("SE/humi.ogg");
    Sounds[6] = LoadSoundMem("SE/koura.ogg");
    Sounds[7] = LoadSoundMem("SE/dokan.ogg");
    Sounds[8] = LoadSoundMem("SE/brockkinoko.ogg");
    Sounds[9] = LoadSoundMem("SE/powerup.ogg");
    Sounds[10] = LoadSoundMem("SE/kirra.ogg");
    Sounds[11] = LoadSoundMem("SE/goal.ogg");
    Sounds[12] = LoadSoundMem("SE/death.ogg");
    Sounds[13] = LoadSoundMem("SE/Pswitch.ogg");
    Sounds[14] = LoadSoundMem("SE/jumpBlock.ogg");
    Sounds[15] = LoadSoundMem("SE/hintBlock.ogg");
    Sounds[16] = LoadSoundMem("SE/4-clear.ogg");
    Sounds[17] = LoadSoundMem("SE/allclear.ogg");
    Sounds[18] = LoadSoundMem("SE/tekifire.ogg");

    //}catch( int num){end();}

    // ループ設定-20000-20秒
    // SetLoopPosSoundMem( 1,Sounds[104]) ;
    // SetLoopSamplePosSoundMem(44100,Sounds[104]);
    // SetLoopSamplePosSoundMem(22050,Sounds[104]);
}

extern bool sound;
void parseArgs(int argc, char *argv[])
{
    if (argc <= 1)
        return;
    for (int i = 0; i < argc; i++)
    {
        //+KZ: why only 1 dash? added a 2 dashes version, keep old for back-compat
        if (
            !strcasecmp(argv[i], "-nosound") ||
            !memcmp(argv[i], "--nosound", sizeof("--nosound"))
        )
        {
            sound = false;
        }

        //+KZ: --help
        //also yeah im just using printf
        if(
            !memcmp(argv[i], "--help", sizeof("--help")) ||
            !memcmp(argv[i], "-h", sizeof("-h"))
        )
        {
            printf("SyobonKZ -- Syobon Action +KZ Edition\n");
            printf("\n");
            printf("Usage: SyobonAction [--option]\n");
            printf("\n");
            printf("Options:\n");
            printf("    -h, --help               Shows this screen\n");
            printf("    -nosound, --nosound      Muted game\n");
            printf("    --fullscreen             Start in full screen\n");

            HelpFlagHandled = true;
        }

        //Fullscreen
        if(
            !memcmp(argv[i], "--fullscreen", sizeof("--fullscreen"))
        )
        {
            StartFullScreenFlag = true;
        }
    }
}
