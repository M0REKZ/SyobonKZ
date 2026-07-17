
//Variables used in Syobon Action game:

#include "global_vars.h"

//String 使用

//プログラム中
//main-10
//タイトル-100

//: This is unexcusable. How could someone in their right mind define
//: a variable called 'main'!?
//: The new define is after the main method
ESyobonGameState SyobonState = ESyobonGameState::TITLE;
int SyobonStateTimer = 0;

//ステージ
ELevelType LevelType = ELevelType::OVERWORLD;
int SyobonWorld;
int SyobonLevel;
int SyobonSection;

//クイック
int fast = 0;

//トラップ表示
int TrapDisplay = 0;

//中間ゲート
int CurrentPlayerCheckpoint = 0;


//スタッフロール
int ending = 0;


//ステージ読み込みループ(いじらない) (Stage loading loop (do not modify))
//+KZ removed "int stagerr" because was unused
int stagepoint;
//オーバーフローさせる
int SyobonRandomMode = 0;

//ステージスイッチ
int stageonoff = 0;


//メインプログラム
int SyobonQuit;

//描画
Uint32 color;
Uint32 gfxcolor;

int mirror;


//1-ステージ
//10-ステージ前
//



//ループ
int t, tt, t1, t2, t3, t4;


//初期化
int InGameInitialized;//, zzxon; //+KZ: zzxon is unused

//キーコンフィグ
//int key;//, keytm; //+KZ: keytm is useless... no wait both are useless/unused

//三角関数
double pai = 3.1415926535;



//プレイヤー
int WarpZoneMessageState;


//メッセージブロック
// +KZ: tmsgx, tmsgnobix, tmsgnobiy, were unused
int TextBoxTimer, TextBoxState, TextBoxSizeY, TextBoxMessageID;





//スクロール範囲
int fx = 0, fy = 0, fzx, fzy, scrollx, scrolly;
//全体のポイント

//: "fma" already exists, so call it something else and add a define
//int fmaZ = 0, fmb = 0;

//強制スクロール
int kscroll = 0;
//画面サイズ(ファミコンサイズ×2)(256-224)
int fxmax = SYOBONKZ_SCREEN_SIZE_X * 100, fymax = SYOBONKZ_SCREEN_SIZE_Y * 100;



//ステージ
ELegacyStageDate LegacyStageDate[17][2001];

//画面黒
int blacktm = 1, blackx = 0;



//自由な値
int xx[91];
double xd[11];
std::string xs[31];


//タイマー測定
//: Do with this what we did with fma
long stimeZ;

//+KZ
ESyobonActionGame currentGame = ESyobonActionGame::SHOBON_NO_ACTION_1_AND_2;
bool HelpFlagHandled = false;
bool StartFullScreenFlag = false;
bool SADevGamesEnabled = false;
bool SyobonStartGame = false;
bool ScreenshotKeyState = false;
bool GIFKeyState = false;
