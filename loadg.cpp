#include "DxLib.h"
#include "global_vars.h"
#include "main.h"
#include "loadg.h"
#include "entities.h"

SDL_Surface *Sliced_GFX[161][8];
SDL_Surface *Main_GFX[51];
SyobonKZMusic *Music[7]; //+KZ increased for Syobon Action 2 music
SyobonKZChunk *Sounds[19];

// +KZ: i added these
SDL_Surface *Main_GFX_KZ[MAIN_GFX_KZ_MAX]; //+KZ
SDL_Surface *Sliced_GFX_KZ[SLICED_GFX_KZ_MAX]; //+KZ
SyobonKZChunk *Sounds_KZ[SOUNDS_KZ_MAX]; //+KZ


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
    Main_GFX_KZ[0] = LoadGraph("res/kz/decoration_kz.png");
    Main_GFX_KZ[1] = LoadGraph("res/sa3/title.png", false);
    Main_GFX_KZ[2] = LoadGraph("res/sa3/spike.png", false);
    Main_GFX_KZ[3] = LoadGraph("res/sa3/big_stone_ball_1.png", false);
    Main_GFX_KZ[4] = LoadGraph("res/sa3/big_stone_ball_2.png", false);
    Main_GFX_KZ[5] = LoadGraph("res/sa3/big_stone_ball_3.png", false);
    Main_GFX_KZ[6] = LoadGraph("res/sa3/big_stone_ball_4.png", false);
    Main_GFX_KZ[7] = LoadGraph("res/sa3/big_stone_ball_5.png", false);
    Main_GFX_KZ[8] = LoadGraph("res/sa3/big_stone_ball_6.png", false);
    Main_GFX_KZ[9] = LoadGraph("res/sa3/jumpscare_plant_1.png", false);
    Main_GFX_KZ[10] = LoadGraph("res/sa3/jumpscare_plant_2.png", false);
    Main_GFX_KZ[11] = LoadGraph("res/kz/levelicons.png", false);
    Main_GFX_KZ[12] = LoadGraph("res/kaizosyobon/syobon3.png", false);
    Main_GFX_KZ[13] = LoadGraph("res/kz/logo.png", false);
    Main_GFX_KZ[14] = LoadGraph("res/jam/logojam.png", false);
    Main_GFX_KZ[15] = LoadGraph("res/kz/arrow.png", false);
    Main_GFX_KZ[16] = LoadGraph("res/sa3/spike_down.png", false);
    Main_GFX_KZ[17] = LoadGraph("res/sa3/brick_brittle.png", false);
    Main_GFX_KZ[18] = LoadGraph("res/sa3/flying_shell_jien_1.png", false);
    Main_GFX_KZ[19] = LoadGraph("res/sa3/flying_shell_jien_2.png", false);
    Main_GFX_KZ[20] = LoadGraph("res/kz/logo_main.png", false);
    Main_GFX_KZ[21] = LoadGraph("res/better/jien_super_shobon.png", false);
    Main_GFX_KZ[22] = LoadGraph("res/better/shell_jien_super_shobon.png", false);
    Main_GFX_KZ[23] = LoadGraph("res/better/super_jien_super_shobon_1.png", false);
    Main_GFX_KZ[24] = LoadGraph("res/better/super_jien_super_shobon_2.png", false);
    Main_GFX_KZ[25] = LoadGraph("res/better/kuma_super_shobon_2.png", false);
    Main_GFX_KZ[26] = LoadGraph("res/better/defrag_super_shobon_1.png", false);
    Main_GFX_KZ[27] = LoadGraph("res/better/defrag_super_shobon_2.png", false);

    Sliced_GFX_KZ[0] = DerivationGraph(0, 0, 64, 29, Main_GFX_KZ[0]);
    Sliced_GFX_KZ[1] = DerivationGraph(0, 31, 70, 40, Main_GFX_KZ[0]);
    Sliced_GFX_KZ[2] = DerivationGraph(0, 0, 19, 19, Main_GFX_KZ[11]);
    Sliced_GFX_KZ[3] = DerivationGraph(19, 0, 19, 19, Main_GFX_KZ[11]);
    Sliced_GFX_KZ[4] = DerivationGraph(38, 0, 19, 19, Main_GFX_KZ[11]);
    Sliced_GFX_KZ[5] = DerivationGraph(32, 35, 30, 30, Main_GFX[2]);
    Sliced_GFX_KZ[6] = DerivationGraph( 0, 182, 40, 60, Main_GFX[4]); //Syobon Action 1 Checkpoint flag
    Sliced_GFX_KZ[7] = DerivationGraph(33 * 8, 0, 30, 30, Main_GFX[1]); //Open eyes cloud block

    // プレイヤー読み込み (Player loading)
    Sliced_GFX[40][0] = DerivationGraph(0, 0, 30, 36, Main_GFX[0]);
    Sliced_GFX[0][0] = DerivationGraph(31 * 4, 0, 30, 36, Main_GFX[0]);
    Sliced_GFX[1][0] = DerivationGraph(31 * 1, 0, 30, 36, Main_GFX[0]);
    Sliced_GFX[2][0] = DerivationGraph(31 * 2, 0, 30, 36, Main_GFX[0]);
    Sliced_GFX[3][0] = DerivationGraph(31 * 3, 0, 30, 36, Main_GFX[0]);
    Sliced_GFX[41][0] = DerivationGraph(50, 0, 51, 73, Main_GFX[6]);

    //x1 = 1;
    // ブロック読み込み (Block loading)
    for (t = 0; t <= 6; t++)
    {
        Sliced_GFX[t][1] = DerivationGraph(33 * t, 0, 30, 30, Main_GFX[1]);
        Sliced_GFX[t + 30][1] = DerivationGraph(33 * t, 33, 30, 30, Main_GFX[1]);
        Sliced_GFX[t + 60][1] = DerivationGraph(33 * t, 66, 30, 30, Main_GFX[1]);
        Sliced_GFX[t + 90][1] = DerivationGraph(33 * t, 99, 30, 30, Main_GFX[1]);
    }
    //Cloud Block
    Sliced_GFX[8][1] = DerivationGraph(33 * 7, 0, 30, 30, Main_GFX[1]);

    //Trampoline
    Sliced_GFX[16][1] = DerivationGraph(33 * 6, 0, 24, 27, Main_GFX[2]);

    //Spikes
    Sliced_GFX[10][1] = DerivationGraph(33 * 9, 0, 30, 30, Main_GFX[1]);
    Sliced_GFX[40][1] = DerivationGraph(33 * 9, 33, 30, 30, Main_GFX[1]);
    Sliced_GFX[70][1] = DerivationGraph(33 * 9, 66, 30, 30, Main_GFX[1]);
    Sliced_GFX[100][1] = DerivationGraph(33 * 9, 99, 30, 30, Main_GFX[1]);
    // ブロック読み込み2 (Block loading 2)
    //x1 = 5;
    for (t = 0; t <= 6; t++)
    {
        Sliced_GFX[t][5] = DerivationGraph(33 * t, 0, 30, 30, Main_GFX[5]);
    }
    Sliced_GFX[10][5] = DerivationGraph(33 * 1, 33, 30, 30, Main_GFX[5]);
    Sliced_GFX[11][5] = DerivationGraph(33 * 2, 33, 30, 30, Main_GFX[5]);
    Sliced_GFX[12][5] = DerivationGraph(33 * 0, 66, 30, 30, Main_GFX[5]);
    Sliced_GFX[13][5] = DerivationGraph(33 * 1, 66, 30, 30, Main_GFX[5]);
    Sliced_GFX[14][5] = DerivationGraph(33 * 2, 66, 30, 30, Main_GFX[5]);

    // アイテム読み込み (Item loading)
    //x1 = 2;
    for (t = 0; t <= 5; t++)
    {
        Sliced_GFX[t][2] = DerivationGraph(33 * t, 0, 30, 30, Main_GFX[2]);
    }

    // 敵キャラ読み込み (Loading enemy characters)
    //x1 = 3;
    Sliced_GFX[0][3] = DerivationGraph(33 * 0, 0, 30, 30, Main_GFX[3]);
    Sliced_GFX[1][3] = DerivationGraph(33 * 1, 0, 30, 43, Main_GFX[3]);
    Sliced_GFX[2][3] = DerivationGraph(33 * 2, 0, 30, 30, Main_GFX[3]);
    Sliced_GFX[3][3] = DerivationGraph(33 * 3, 0, 30, 44, Main_GFX[3]);
    Sliced_GFX[4][3] = DerivationGraph(33 * 4, 0, 33, 35, Main_GFX[3]);
    Sliced_GFX[5][3] = DerivationGraph(0, 0, 37, 55, Main_GFX[7]);
    Sliced_GFX[6][3] = DerivationGraph(38 * 2, 0, 36, 50, Main_GFX[7]);
    Sliced_GFX[150][3] = DerivationGraph(38 * 2 + 37 * 2, 0, 36, 50, Main_GFX[7]);
    Sliced_GFX[7][3] = DerivationGraph(33 * 6 + 1, 0, 32, 32, Main_GFX[3]);
    Sliced_GFX[8][3] = DerivationGraph(38 * 2 + 37 * 3, 0, 37, 47, Main_GFX[7]);
    Sliced_GFX[151][3] = DerivationGraph(38 * 3 + 37 * 3, 0, 37, 47, Main_GFX[7]);
    Sliced_GFX[9][3] = DerivationGraph(33 * 7 + 1, 0, 26, 30, Main_GFX[3]);
    Sliced_GFX[10][3] = DerivationGraph(214, 0, 46, 16, Main_GFX[6]);

    // モララー (Molalla)
    Sliced_GFX[30][3] = DerivationGraph(0, 56, 30, 36, Main_GFX[7]);
    Sliced_GFX[155][3] = DerivationGraph(31 * 3, 56, 30, 36, Main_GFX[7]);
    Sliced_GFX[31][3] = DerivationGraph(50, 74, 49, 79, Main_GFX[6]);

    Sliced_GFX[80][3] = DerivationGraph(151, 31, 70, 40, Main_GFX[4]);
    Sliced_GFX[81][3] = DerivationGraph(151, 72, 70, 40, Main_GFX[4]);
    Sliced_GFX[130][3] = DerivationGraph(151 + 71, 72, 70, 40, Main_GFX[4]);
    Sliced_GFX[82][3] = DerivationGraph(33 * 1, 0, 30, 30, Main_GFX[5]);
    Sliced_GFX[83][3] = DerivationGraph(0, 0, 49, 48, Main_GFX[6]);
    Sliced_GFX[84][3] = DerivationGraph(33 * 5 + 1, 0, 30, 30, Main_GFX[3]);
    Sliced_GFX[86][3] = DerivationGraph(102, 66, 49, 59, Main_GFX[6]);
    Sliced_GFX[152][3] = DerivationGraph(152, 66, 49, 59, Main_GFX[6]);

    Sliced_GFX[90][3] = DerivationGraph(102, 0, 64, 63, Main_GFX[6]);

    Sliced_GFX[100][3] = DerivationGraph(33 * 1, 0, 30, 30, Main_GFX[2]);
    Sliced_GFX[101][3] = DerivationGraph(33 * 7, 0, 30, 30, Main_GFX[2]);
    Sliced_GFX[102][3] = DerivationGraph(33 * 3, 0, 30, 30, Main_GFX[2]);

    // Sliced_GFX[104][3] = DerivationGraph( 33*2, 0, 30, 30, Main_GFX[5]) ;
    Sliced_GFX[105][3] = DerivationGraph(33 * 5, 0, 30, 30, Main_GFX[2]);
    Sliced_GFX[110][3] = DerivationGraph(33 * 4, 0, 30, 30, Main_GFX[2]);

    // 背景読み込み (Background loading)
    //x1 = 4;
    Sliced_GFX[0][4] = DerivationGraph(0, 0, 150, 90, Main_GFX[4]);
    Sliced_GFX[1][4] = DerivationGraph(151, 0, 65, 29, Main_GFX[4]);
    Sliced_GFX[2][4] = DerivationGraph(151, 31, 70, 40, Main_GFX[4]);
    Sliced_GFX[3][4] = DerivationGraph(0, 91, 100, 90, Main_GFX[4]);
    Sliced_GFX[4][4] = DerivationGraph(151, 113, 51, 29, Main_GFX[4]);
    Sliced_GFX[5][4] = DerivationGraph(222, 0, 28, 60, Main_GFX[4]);
    Sliced_GFX[6][4] = DerivationGraph(151, 143, 90, 40, Main_GFX[4]);

    //+KZ: just realized this is a non-existent graphic, see below for explanation
    Sliced_GFX[30][4] = DerivationGraph(293, 0, 149, 90, Main_GFX[4]);

    //+KZ: Sliced_GFX[31][4] is 3-1 grass?? 3-1 also wants a Sliced_GFX[32][4] sprite, which seems to be a cloud
    // sadly there is not a official Syobon Action 2 release containing the missing sprites.
    // Sliced_GFX[32][4] was not even in this list, so probably the creator of that mod
    // forgot to upload loadg.cpp and the assets in the latest game zip...
    // im using alternative edited versions for now
    //
    // dont uncomment this, im using Sliced_GFX_KZ directly now
    //Sliced_GFX[31][4] = Sliced_GFX_KZ[0]; // DerivationGraph(293, 92, 64, 29, Main_GFX[4]);
    //Sliced_GFX[32][4] = Sliced_GFX_KZ[1];
    //

    // 中間フラグ (Intermediate flag)
    //+KZ: 42 to fix gray line, previously it was 40
    //Original Syobon Action had it in 0, i prefer the version with text
    Sliced_GFX[20][4] = DerivationGraph(42, 182, 40, 60, Main_GFX[4]);

    // グラ
    //x1 = 5;
    Sliced_GFX[0][5] = DerivationGraph(167, 0, 45, 45, Main_GFX[6]);

    // 敵サイズ収得
    // int GrHandle=0;
    //x1 = 3;
    for (t = 0; t <= 140; t++)
    {
        if (Sliced_GFX[t][3])
        {
            EnemyDefaultSizeX[t] = Sliced_GFX[t][3]->w;
            EnemyDefaultSizeY[t] = Sliced_GFX[t][3]->h;
            // GetGraphSize(Sliced_GFX[t][3] ,&anx[t] ,&any[t]);
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
    //x1 = 4;
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

    Sounds[1] = LoadSoundMem("SE/jump.wav");
    // Sounds[2] = LoadSoundMem("SE/brockcoin.ogg");
    Sounds[3] = LoadSoundMem("SE/brockbreak.wav");
    Sounds[4] = LoadSoundMem("SE/coin.wav");
    Sounds[5] = LoadSoundMem("SE/humi.wav");
    Sounds[6] = LoadSoundMem("SE/koura.wav");
    Sounds[7] = LoadSoundMem("SE/dokan.wav");
    Sounds[8] = LoadSoundMem("SE/brockkinoko.wav");
    Sounds[9] = LoadSoundMem("SE/powerup.wav");
    Sounds[10] = LoadSoundMem("SE/kirra.wav");
    Sounds[11] = LoadSoundMem("SE/goal.ogg");
    Sounds[12] = LoadSoundMem("SE/death.wav");
    Sounds[13] = LoadSoundMem("SE/Pswitch.wav");
    Sounds[14] = LoadSoundMem("SE/jumpBlock.wav");
    Sounds[15] = LoadSoundMem("SE/hintBlock.wav");
    Sounds[16] = LoadSoundMem("SE/4-clear.wav");
    Sounds[17] = LoadSoundMem("SE/allclear.wav");
    Sounds[18] = LoadSoundMem("SE/tekifire.wav");

    //+KZ
    Sounds_KZ[0] = LoadSoundMem("SE/sa3/so_piranhaeat.wav");
    Sounds_KZ[1] = LoadSoundMem("SE/sa3/so_1up.wav");

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
            printf("    --trap-display           Show trap triggers (for testing)\n");
            printf("    --fast-death             Skip death animation\n");
            printf("\n");
            printf("    --dev-games               Enable unfinished development games\n");

            HelpFlagHandled = true;
        }

        //Fullscreen
        if(
            !memcmp(argv[i], "--fullscreen", sizeof("--fullscreen"))
        )
        {
            StartFullScreenFlag = true;
        }

        //TrapDisplay
        if(
            !memcmp(argv[i], "--trap-display", sizeof("--trap-display"))
        )
        {
            TrapDisplay = true;
        }

        //fast death
        if(
            !memcmp(argv[i], "--fast-death", sizeof("--fast-death"))
        )
        {
            fast = true;
        }

        //SA3 (for now)
        if(
            !memcmp(argv[i], "--dev-games", sizeof("--dev-games"))
        )
        {
            SADevGamesEnabled = true;
        }
    }
}
