#include <string>
#include <limits>
#include "level_enums.hpp"
#include "DxLib.h"

#ifndef SYOBON_GLOBAL_VARS_H
#define SYOBON_GLOBAL_VARS_H

//プログラム中
//main-10
//タイトル-100

enum class ESyobonGameState : int
{
    IN_GAME = 1,
    CREDITS = 2,
    LIVES_SPLASH = 10,
    TITLE = 100,

    //+KZ
    PAUSE, //ONLY SET THIS ONE WITH TogglePauseState()!!!!
};
//Open Syobon Action:
// This is unexcusable. How could someone in their right mind define
// a variable called 'main'!?
// The new define is after the main method
//
// @attention +KZ: int mainZ is now ESyobonGameState SyobonState
extern ESyobonGameState SyobonState;
// @attention +KZ: int maintm is now int SyobonStateTimer
extern int SyobonStateTimer;

//ステージ (Stage)
// @attention +KZ: int stagecolor is now LevelType LevelType
extern ELevelType LevelType;
// @attention +KZ: int sta is now int SyobonWorld
extern int SyobonWorld;
// @attention +KZ: int stb is now int SyobonLevel
extern int SyobonLevel;
// @attention +KZ: int stc is now int SyobonSection
extern int SyobonSection;

//クイック (Quick)
extern int fast;

//トラップ表示 (Trap display) //+KZ: Enabling this will show trap hit boxes in-game
extern int TrapDisplay;

//中間ゲート (Intermediate gate)
// @attention +KZ: int tyuukan is now int CurrentPlayerCheckpoint
extern int CurrentPlayerCheckpoint;


//スタッフロール
extern int ending;


//ステージ読み込みループ(いじらない) (Stage loading loop (do not modify))
//+KZ removed "int stagerr" because was unused
extern int stagepoint;
//オーバーフローさせる (Overflow)
// @attention +KZ: int over is now int SyobonRandomMode
extern int SyobonRandomMode;

//ステージスイッチ (Stage Switch)
//+KZ: ON/OFF Tile
extern int stageonoff;

//メインプログラム (Main Program)
// @attention +KZ: int maint is now int SyobonQuit
extern int SyobonQuit;

//描画 (Drawing)
extern Uint32 color;
extern Uint32 gfxcolor;

//+KZ: mirrors the image drawn by drawimage()
extern int mirror;

//1-ステージ (1-Stage)
//10-ステージ前 (10-Before Stage)
//


//初期化 (Initialization)
extern int InGameInitialized;//, zzxon; //+KZ: zzxon is unused

//キーコンフィグ (Key Configuration)
//extern int key;//, keytm; //+KZ: keytm is useless... no wait both are useless/unused

//三角関数 (Trigonometric functions)
extern double pai;

//@attention +KZ: int mainmsgtype is now int WarpZoneMessageState
extern int WarpZoneMessageState;


//メッセージブロック (Message Block)
// @attention +KZ: They were int tmsgtm, tmsgtype, tmsgy, tmsg;
// +KZ: tmsgx, tmsgnobix, tmsgnobiy, were unused
extern int TextBoxTimer, TextBoxState, TextBoxSizeY, TextBoxMessageID;





//スクロール範囲 (Scroll range)
//+KZ: i still dont rename some of these since i dont understand the purpose of fzx
extern int fx, fy, fzx, scrollx;
extern int scrolly; //+KZ: used but never initialized!
extern int fzy; //+KZ: unused, but i may want to give it a use in the future
//全体のポイント (Overall points)

//Open Syobon Action: "fma" already exists, so call it something else and add a define
//+KZ: done
//+KZ later: the values are always 0 and never modified, so they are useless
//extern int fmaZ;
//extern int fmb;

//強制スクロール (Force Scroll)
extern int kscroll;
//画面サイズ(ファミコンサイズ×2)(256-224) (Screen size (NES size x 2) (256 x 224))
extern int fxmax, fymax;



//ステージ (Stage)
// @attention +KZ: byte LegacyStageDate[17][2001] now is ELegacyStageDate LegacyStageDate[17][2001]
extern ELegacyStageDate LegacyStageDate[17][2001];

//画面黒 (Black screen)
extern int blacktm, blackx;



//+KZ: these should be just local variables in many places
//  but we can not replace them in a crazy way, make sure
//  it wont break anything in the game.
//自由な値 (Free value)
extern int xx[91];
extern double xd[11];
extern std::string xs[31];
//ループ (Loop)
extern int t, tt, t1, t2, t3, t4;


//タイマー測定 (Timer measurement)
//Open Syobon Action: Do with this what we did with fma
extern long stimeZ;

//+KZ
#define PLUSKZ_EDITION_TEXT "+KZ Edition"
#define PLUSKZ_REMAKE_TEXT "+KZ Remake"

//misc useful defines
#define BLOCK_DEFAULT_SIZE 29
constexpr double GAME_X_POS_TO_DOUBLE(int x_axis) { return ((((double)x_axis) / 100) / BLOCK_DEFAULT_SIZE); }
constexpr double GAME_Y_POS_TO_DOUBLE(int y_axis) { return ((((double)y_axis) / 100 + 12) / BLOCK_DEFAULT_SIZE); }
constexpr int DOUBLE_TO_GAME_X_POS(double x_axis) { return ((int)(x_axis * BLOCK_DEFAULT_SIZE * 100)); }
constexpr int DOUBLE_TO_GAME_Y_POS(double y_axis) { return ((int)((y_axis * BLOCK_DEFAULT_SIZE - 12) * 100)); }

extern bool HelpFlagHandled; // --help cli flag
extern bool StartFullScreenFlag;

//Dont change the IDs or saves will break!!!
enum class ESyobonActionGame : int
{
    SHOBON_NO_ACTION_1_AND_2 = 0,
    SYOBON_ACTION_3 = 300,
    SYOBON_ACTION_JAM = 1350,
    KAIZO_SYOBON = 1500,
    SYOBONKZ_TRUE_ACTION = 3000, //+KZ

    //not actually a game
    SYOBONKZ_CREDITS = 50000, //+KZ

    FIRST = SHOBON_NO_ACTION_1_AND_2,
    LAST = SYOBONKZ_CREDITS,
};
extern ESyobonActionGame currentGame;
extern bool SADevGamesEnabled;
extern bool SyobonStartGame;
extern bool ScreenshotKeyState;
extern bool GIFKeyState;

#endif
