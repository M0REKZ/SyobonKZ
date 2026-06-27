
#include "global_vars.h"
#include "levels.h"
#include "main.h"
#include "entities.h"
#include "title.h"
#include "player.h"
#include "blocks.h"
#include "extra_graphics.h"

std::unordered_map<std::string, SDL_Surface *> apGlobalTexts;

// プログラムは WinMain から始まります
// Changed to ansi c++ main()
// +KZ: Changed to SDL_main :p

#ifdef __ANDROID__
extern "C" int SDL_main(int argc, char *argv[])
#else
int main(int argc, char *argv[])
#endif
{
	#ifdef __ANDROID__
		SDL_SetEventFilter(HandleAppEvents, NULL);
	#endif	
	parseArgs(argc, argv);

	//+KZ: --help
	if(HelpFlagHandled)
		return 0;
	
	if (DxLib_Init() == -1)
	{
		printf("ERROR INIT DXLIB\n");
		return 1;
	}

	// 全ロード
	loadg();

	// フォント
	SetFontSize(20); //this will make font size 20 load into memory
	SetFontSize(16);
	// SetFontThickness(4) ;

	// ループ
	// for (maint=0;maint<=2;maint++){

	//+KZ: Create a loading screen
	SyobonKZFillRect(screen, nullptr, 0);
	DrawString(200, 200, "Loading...", GetColor(255, 255, 255));
	SyobonKZScreenFlip(screen);

	//+KZ: init things that are too CPU consuming
	CreateEntityMessageCache();
	CreatePlayerMessageCache();
	CreateGlobalTextCache();

	MainLoop(); //+KZ

	// ＤＸライブラリ使用の終了処理
	end();
}

// メイン描画 (Main rendering)
void rpaint()
{

	// ダブルバッファリング (Double buffering)
	setcolor(0, 0, 0);
	// if (stagecolor==1)setcolor(170,170,255);
	if (StageColor == ELevelType::OVERWORLD)
		setcolor(160, 180, 250);
	if (StageColor == ELevelType::UNDERGROUND)
		setcolor(10, 10, 10);
	if (StageColor == ELevelType::SKY)
		setcolor(160, 180, 250);
	if (StageColor == ELevelType::CASTLE)
		setcolor(10, 10, 10);
	if (StageColor == ELevelType::ICY)
	{
		setcolor(160, 180, 250);
		PlayerGroundType = EPlayerGroundType::SLIP;
	}
	else
	{
		PlayerGroundType = EPlayerGroundType::NORMAL;
	}

	//: Clear screen
	FillScreen();

	if (SyobonState == ESyobonState::IN_GAME && zxon >= 1)
	{
		RenderBackground();

		RenderExtraGraphics();

		RenderLifts();

		RenderPlayer();

		mirror = 0;

		RenderEnemies();

		RenderBlocks();

		RenderWalls();

		RenderOverwritePipe(); //+KZ: ??

		RenderEnemiesTwo();

		HandlePlayerMessage();
		HandleEnemiesMessages();

		// メッセージブロック (Message Block)
		if (tmsgtm > 0)
		{
			ttmsg();
			if (tmsgtype == 1)
			{
				xx[0] = 1200;
				tmsgy += xx[0];
				if (tmsgtm == 1)
				{
					tmsgtm = 80000000;
					tmsgtype = 2;
				}
			} // 1

			else if (tmsgtype == 2)
			{
				tmsgy = 0;
				tmsgtype = 3;
				tmsgtm = 15 + 1;
				#ifdef SYOBON_WAIT_KEY_MSGBOX_FIX
				WaitKey();
				#endif
			}

			else if (tmsgtype == 3)
			{
				xx[0] = 1200;
				tmsgy += xx[0];
				#ifndef SYOBON_WAIT_KEY_MSGBOX_FIX
				if (tmsgtm == 15) //+KZ: WaitKey() works better above for emscripten
					WaitKey();
				#endif
				if (tmsgtm == 1)
				{
					tmsgtm = 0;
					tmsgtype = 0;
					tmsgy = 0;
				}
			} // 1

			tmsgtm--;
		} // tmsgtm

		// メッセージ (Message)
		if (mainmsgtype >= 1) //+KZ: 1-2 Warp zone
		{
			setfont(20, 4);
			if (mainmsgtype == 1)
			{
				DrawGraphZ(126, 100, apGlobalTexts["WELCOME TO OWATA ZONE"]);
				for (t2 = 0; t2 <= 2; t2++)
					DrawGraphZ(88 + t2 * 143, 210, apGlobalTexts["1"]);
			}
			setfont(20, 5);
		} // mainmsgtype>=1

		// 画面黒 (Black screen)
		if (blacktm > 0)
		{
			blacktm--;
			fillrect(0, 0, fxmax, fymax);
			if (blacktm == 0)
			{
				if (blackx == 1)
				{
					zxon = 0;
				}
			}

		} // blacktm
	}

	if (SyobonState == ESyobonState::CREDITS)
	{

		setcolor(255, 255, 255);
		DrawGraphZ(240 - 13 * 20 / 2, xx[12] / 100, apGlobalTexts["制作・プレイに関わった方々"]);
		DrawGraphZ(240 - 9 * 20 / 2, xx[13] / 100, apGlobalTexts["ステージ１　プレイ"]);
		DrawGraphZ(240 - 6 * 20 / 2, xx[14] / 100, apGlobalTexts["先輩　Ｘ～Ｚ"]);
		DrawGraphZ(240 - 9 * 20 / 2, xx[15] / 100, apGlobalTexts["ステージ２　プレイ"]);
		DrawGraphZ(240 - 8 * 20 / 2, xx[16] / 100, apGlobalTexts["友人　willowlet "]);
		DrawGraphZ(240 - 9 * 20 / 2, xx[17] / 100, apGlobalTexts["ステージ３　プレイ"]);
		DrawGraphZ(240 - 8 * 20 / 2, xx[18] / 100, apGlobalTexts["友人　willowlet "]);
		DrawGraphZ(240 - 9 * 20 / 2, xx[19] / 100, apGlobalTexts["ステージ４　プレイ"]);
		DrawGraphZ(240 - 6 * 20 / 2, xx[20] / 100, apGlobalTexts["友人２　ann "]);
		DrawGraphZ(240 - 3 * 20 / 2, xx[21] / 100, apGlobalTexts["ご協力"]);
		DrawGraphZ(240 - 3 * 20 / 2, xx[22] / 100, apGlobalTexts["Ｔ先輩"]);
		DrawGraphZ(240 - 3 * 20 / 2, xx[23] / 100, apGlobalTexts["Ｓ先輩"]);
		DrawGraphZ(240 - 6 * 20 / 2, xx[24] / 100, apGlobalTexts["動画技術提供"]);
		DrawGraphZ(240 - 3 * 20 / 2, xx[25] / 100, apGlobalTexts["Ｋ先輩"]);
		DrawGraphZ(240 - 16 * 20 / 2, xx[26] / 100, apGlobalTexts["動画キャプチャ・編集・エンコード"]);
		DrawGraphZ(240 - 5 * 20 / 2, xx[27] / 100, apGlobalTexts["willowlet "]);
		DrawGraphZ(240 - 16 * 20 / 2, xx[28] / 100, apGlobalTexts["プログラム・描画・ネタ・動画編集"]);
		DrawGraphZ(240 - 2 * 20 / 2, xx[29] / 100, apGlobalTexts["ちく"]);

		DrawGraphZ(240 - 22 * 20 / 2, xx[30] / 100, apGlobalTexts["プレイしていただき　ありがとうございました〜"]);
	}
	// Showing lives
	if (SyobonState == ESyobonState::LIVES_SPLASH)
	{

		setc0();
		FillScreen();

		SetFontSize(16);
		SetFontThickness(4);

		drawimage(Sliced_GFX[0][0], 190, 190);
		DrawFormatString(230, 200, GetColor(255, 255, 255), " × %d",
						 Lives);
	}
	// タイトル (Title)
	if (SyobonState == ESyobonState::TITLE)
	{

		setcolor(160, 180, 250);
		fillrect(0, 0, fxmax, fymax);

		//+KZ
		setcolor(0, 0, 0);
		str(PLUSKZ_EDITION_TEXT, 480 / 2 - (sizeof(PLUSKZ_EDITION_TEXT) * 10) / 2, 120);

		drawimage(Main_GFX[30], 240 - 380 / 2, 60);

		drawimage(Sliced_GFX[0][4], 12 * 30, 10 * 29 - 12);
		drawimage(Sliced_GFX[1][4], 6 * 30, 12 * 29 - 12);

		// プレイヤー
		drawimage(Sliced_GFX[0][0], 2 * 30, 12 * 29 - 12 - 6);
		for (t = 0; t <= 16; t++)
		{
			drawimage(Sliced_GFX[5][1], 29 * t, 13 * 29 - 12);
			drawimage(Sliced_GFX[6][1], 29 * t, 14 * 29 - 12);
		}

		setcolor(0, 0, 0);
		str("Enterキーを押せ!!", 240 - 8 * 20 / 2, 250);
	}
	SyobonKZScreenFlip(screen);

} // rpaint()

// メインプログラム (Main Program)
void Mainprogram()
{

	stimeZ = long(GetNowCount());

	if (ending == 1)
		SyobonState = ESyobonState::CREDITS;

	// キー (Key)

	if (SyobonState == ESyobonState::IN_GAME && tmsgtype == 0)
	{

		//+KZ: Init
		if (zxon == 0)
		{
			zxon = 1;
			mainmsgtype = 0;

			StageColor = ELevelType::OVERWORLD;
			PlayerX = 5600;
			PlayerY = 32000;
			PlayerLookingDirection = 1;
			Health = 1;
			PlayerVelX = 0;
			PlayerVelY = 0;
			PlayerSizeX = 3000;
			PlayerSizeY = 3600;

			PlayerState = 0;

			fx = 0;
			fy = 0;
			fzx = 0;
			stageonoff = 0;

			// チーターマン　入れ (Cheetahmen)
			//bgmchange(Music[1]);

			stagecls();

			stage();

			// ランダムにさせる (Make it random)
			if (SyobonRandomMode == 1)
			{
				for (t = 0; t < tmax; t++)
				{
					if (SyobonRand(3) <= 1)
					{
						BlockX[t] = (SyobonRand(500) - 1) * 29 * 100;
						BlockY[t] = SyobonRand(14) * 100 * 29 - 1200;
						BlockType[t] = (EBlockType)SyobonRand(142);
						if ((int)BlockType[t] >= 9 && (int)BlockType[t] <= 99)
						{
							BlockType[t] = (EBlockType)SyobonRand(8);
						}
						BlockSubType[t] = SyobonRand(4);
					}
				}
				for (t = 0; t < bmax; t++)
				{
					if (SyobonRand(2) <= 1)
					{
						EnemyAppearX[t] = (SyobonRand(500) - 1) * 29 * 100;
						EnemyAppearY[t] = SyobonRand(15) * 100 * 29 - 1200 - 3000;
						if (SyobonRand(6) == 0)
						{
							EnemyAppearType[t] = (EEnemyType)SyobonRand(9);
						}
					}
				}

				LiftCount = 0;
				t = LiftCount;
				LiftX[t] = PlayerX + fx;
				LiftY[t] = (13 * 29 - 12) * 100;
				LiftSizeX[t] = 30 * 100;
				srtype[t] = 0;
				sracttype[t] = 0;
				LiftVelY[t] = 0;
				srsp[t] = 0;
				LiftCount++;

				if (SyobonRand(4) == 0)
					StageColor = (ELevelType)SyobonRand(5);
			}

		} // zxon

		HandlePlayer();

		// キー入力初期化 (Key input initialization)
		// for (t=0;t<=6;t++)
		actaon[0] = 0;
		actaon[4] = 0;

		HandleLifts();

		HandleExtraGraphics();

		PlaceEntities();
		HandleEntities();

		// スクロール (Scroll)
		// xx[0]=xx[0];
		// x
		if (kscroll != 1 && kscroll != 2)
		{
			xx[2] = mascrollmax;
			xx[3] = 0;
			xx[1] = xx[2];
			if (PlayerX > xx[1] && fzx < scrollx)
			{
				xx[5] = PlayerX - xx[1];
				PlayerX = xx[1];
				fx += xx[5];
				fzx += xx[5];
				if (xx[1] <= 5000)
					xx[3] = 1;
			}
			// if (kscroll!=5){//戻りなし (No Return)
			// xx[1]=xx[2]-500;if (ma<xx[1] && fzx>700){xx[5]=xx[1]-ma;ma=xx[1];fx-=xx[5];fzx-=xx[5];}
			// }
			// if (xx[3]==1){if (tyuukan==1)tyuukan=1;}
		} // kscroll

	} // if (mainZ==1){

	// スタッフロール (Staff Roll)
	if (SyobonState == ESyobonState::CREDITS)
	{
		SyobonStateTimer++;

		xx[7] = 46;
		if (CheckHitKey(KEY_INPUT_1) == 1)
		{
			end();
		}
		if (CheckHitKey(KEY_INPUT_SPACE) == 1)
		{
			for (t = 0; t <= xx[7]; t += 1)
			{
				xx[12 + t] -= 300;
			}
		}

		if (SyobonStateTimer <= 1)
		{
			SyobonStateTimer = 2;
			bgmchange(Music[5]);
			xx[10] = 0;
			for (t = 0; t <= xx[7]; t += 1)
			{
				xx[12 + t] = 980000;
			}
			// for (t=0;t<=xx[7];t+=2){xx[12+t]=46000;}
			xx[12] = 460;
			xx[13] = 540;
			xx[14] = 590;
			xx[15] = 650;
			xx[16] = 700;
			xx[17] = 760;
			xx[18] = 810;
			xx[19] = 870;
			xx[20] = 920;

			xx[21] = 1000;
			xx[22] = 1050;
			xx[23] = 1100;
			xx[24] = 1180;
			xx[25] = 1230;

			xx[26] = 1360;
			xx[27] = 1410;
			xx[28] = 1540;
			xx[29] = 1590;

			xx[30] = 1800;

			for (t = 0; t <= xx[7]; t += 1)
			{
				xx[12 + t] *= 100;
			}
		}

		xx[10] += 1;
		for (t = 0; t <= xx[7]; t += 1)
		{
			xx[12 + t] -= 100;
		} // t

		if (xx[30] == -200)
		{
			bgmchange(Music[5]);
		}
		if (xx[30] <= -400)
		{
			SyobonState = ESyobonState::TITLE;
			Lives = 2;
			SyobonStateTimer = 0;
			ending = 0;
		}

	} // mainZ==2

	if (SyobonState == ESyobonState::LIVES_SPLASH)
	{
		SyobonStateTimer++;

		if (fast == 1)
			SyobonStateTimer += 2;
		if (SyobonStateTimer >= 30)
		{
			SyobonStateTimer = 0;
			SyobonState = ESyobonState::IN_GAME;
			zxon = 0;
		}
	} // if (mainZ==10){

	// タイトル (Title)
	//+KZ: This is the part that handles pressed keys in title
	if (SyobonState == ESyobonState::TITLE)
	{
		HandleTitleKeys();
	} // 100

	// 描画 (Drawing)
	rpaint();

	// 30-fps
	xx[0] = 30;
	if (CheckHitKey(KEY_INPUT_SPACE) == 1)
	{
		xx[0] = 60;
	}
	//+KZ: on emscripten FPS is done differently and this line is useless, check MainloopEmscripten()
	wait2(stimeZ, long(GetNowCount()), 1000 / xx[0]);

	// wait(20);

} // Mainprogram()

// タイマー測定 (Timer measurement)
void wait2(long starttime, long endtime, int FLAME_TIME)
{
	if (endtime - starttime < FLAME_TIME)
		wait(FLAME_TIME - (endtime - starttime));
}

// 乱数作成 (Random number generation)
int SyobonRand(int Rand)
{
	return rand() % Rand;
}

// 終了 (End)
void deinit()
{
	setc0();
	FillScreen();
	DrawString(200, 200, "EXITING...", GetColor(255, 255, 255));
	SyobonKZScreenFlip(screen);

	// SURFACES
	for (t = 0; t < 51; t++)
		SyobonKZFreeImage(Main_GFX[t]);
	for (int i = 0; i < 161; i++)
		for (int j = 0; j < 8; j++)
			SyobonKZFreeImage(Sliced_GFX[i][j]);
	//--

	// SOUNDS
	for (int i = 1; i < 6; i++)
		SyobonKZFreeMusic(Music[i]);
	for (int i = 1; i < 19; i++)
		SyobonKZFreeChunk(Sounds[i]);
	//--

	// Font
	for (int i = 0; i < FONT_MAX; i++)
		TTF_CloseFont(font[i]);

	// Joystick
	SyobonKZJoystickClose(joystick);

	// Close libraries
	SyobonKZImageQuit();
	TTF_Quit();
	SyobonKZAudioQuit();
	SDL_Quit();
}
// 画像関係 (Image related)
//{
// 色かえ(指定) (Color change (specified))
void setcolor(int red, int green, int blue)
{
	color = GetColor(red, green, blue);
	gfxcolor = GetGFXColor(red, green, blue);
}

// 色かえ(黒)(白) (Color change (black) (white))
// +KZ: using macros for setc0() and setc1() now

// 線 (Line)
void drawline(int a, int b, int c, int d)
{
	SyobonKZLineColor(screen, a, b, c, d, gfxcolor);
}

// 四角形(塗り無し) (Rectangle (unfilled))
void drawrect(int a, int b, int c, int d)
{
	SyobonKZRectangleColor(screen, a, b, a + c - 1, b + d - 1, gfxcolor);
}

// 四角形(塗り有り) (Rectangle (with fill))
void fillrect(int a, int b, int c, int d)
{
	SyobonKZBoxColor(screen, a, b, a + c - 1, b + d - 1, gfxcolor);
}

// 円(塗り無し) (Circle (unfilled))
void drawarc(int a, int b, int c, int d)
{
	SyobonKZEllipseColor(screen, a, b, c, d, gfxcolor);
}

// 円(塗り有り) (Circle (filled))
void fillarc(int a, int b, int c, int d)
{
	SyobonKZFilledEllipseColor(screen, a, b, c, d, gfxcolor);
}

void FillScreen()
{
	SyobonKZFillRect(screen, 0, color);
}

// 画像の読み込み (Image loading)
//+KZ: the two loadimage functions were not used

// 画像表示 (Image display)
void drawimage(SDL_Surface *mx, int a, int b)
{
	if (mirror == 0)
		DrawGraph(a, b, mx, TRUE);
	if (mirror == 1)
		DrawTurnGraph(a, b, mx, TRUE);
}

void drawimage(SDL_Surface *mx, int a, int b, int c, int d, int e, int f)
{
	SDL_Surface *m;
	m = DerivationGraph(c, d, e, f, mx);
	if (mirror == 0)
		DrawGraph(a, b, m, TRUE);
	if (mirror == 1)
		DrawTurnGraph(a, b, m, TRUE);
	SyobonKZFreeImage(m);
}

/*
//文字
void str(char d[],int a,int b){
//char d[]=c;
DrawString(a,b,d,color);
}
*/

// 文字 (Letter)
void str(std::string x, int a, int b)
{
	// char d[]="あ";
	DrawString(a, b, x.c_str(), color);
	// DrawString(10,10,xs[3].c_str(),color);

	xx[2] = 4;
}

/*
//数値を文字に変換
void strchange(string x,int a){
}
*/

/*
//中央にあわせる//(font)
void str1(String c,int r,int b){
int a=0,x=0;
int d=6;

//x=c.length()*d;//tiny.6
x=r*d;
a=120-x/2;

g.drawString(c,a,b);
}
*/

// string→int
/*
char str[] = "12345";
int num;

num = atoi(str);
*/

// 文字ラベル変更 (Change text label)
// +KZ: Why is this empty?
void setfont(int a)
{
	/*
	if (a==0)g.setFont(Font.getFont(Font.SIZE_TINY));
	if (a==1)g.setFont(Font.getFont(Font.SIZE_SMALL));
	if (a==2)g.setFont(Font.getFont(Font.SIZE_MEDIUM));
	if (a==3)g.setFont(Font.getFont(Font.SIZE_LARGE));
	*/
}

// 音楽再生 (Music playback)
void PlaySound(SyobonKZChunk *x)
{
	PlaySoundMem(x, DX_PLAYTYPE_BACK);
}

//+KZ: stacecls, stage and stagep moved to levels.cpp

// BGM変更 (Change background music)
void bgmchange(SyobonKZMusic *x)
{
	SyobonKZHaltMusic();
	// Music[0]=0;
	Music[0] = x;
	SyobonKZPlayMusic(Music[0], -1);

	if (x == Music[2])
		SyobonKZVolumeMusic(SYOBONKZ_MAX_VOLUME * 40 / 100);
	else
		SyobonKZVolumeMusic(SYOBONKZ_MAX_VOLUME * 50 / 100);
} // bgmchange()

// メッセージ (Message)
void ttmsg()
{
	#define txmsg(string, line) DrawGraphZ(66, 46 + line * 24, apGlobalTexts[string]);

	xx[1] = 6000 / 100;
	xx[2] = 4000 / 100;
	if (tmsgtype == 1 || tmsgtype == 2)
	{
		setc0();
		fillrect(xx[1], xx[2], 360, tmsgy / 100);
		setc1();
		drawrect(xx[1], xx[2], 360, tmsgy / 100);
	}
	if (tmsgtype == 2)
	{
		// フォント
		// From Syobon Action All Stars
		if (currentGame == ESyobonActionGame::SYOBON_ACTION_3)
		{
			setfont(18, 11);
		}
		else
		{
			setfont(20, 5);
		}

		if (tmsg == 0)
		{
			setc1();
			// フォント
			setfont(20, 5);
			txmsg("テスト　hoge", 0);
		}

		if (tmsg == 1)
		{
			setc1();
			//txmsg("", 0);
			txmsg("ステージ 1 より", 0);
			txmsg("特殊的なものが増えたので", 1);
			txmsg("気をつけてくれよ〜", 2);
			txmsg("後、アイテムの一部を利用するかも…", 4);
			txmsg("                       ちく より", 6);
		}

		if (tmsg == 2)
		{
			txmsg("            ？が必要です ", 3);
			txmsg("                         m9(^Д^)", 6);
		}

		if (tmsg == 3)
		{
			txmsg("   別にコインに意味ないけどね ", 3);
			txmsg("                      (・ω・ )ﾉｼ", 6);
		}

		if (tmsg == 4)
		{
			txmsg("この先に隠しブロックがあります ", 2);
			txmsg("注意してください !!", 4);
		}

		if (tmsg == 5)
		{
			//txmsg("", 0);
			txmsg(" 前回よりも難易度を下げましたので", 1);
			txmsg(" 気楽にプレイしてください    ", 3);
			txmsg("                       ちく より", 6);
		}

		if (tmsg == 6)
		{
			//txmsg("", 0);
			txmsg(" そこにいる敵のそばによると、      ", 1);
			txmsg(" 自分と一緒にジャンプしてくれます。",
				  2);
			txmsg("   可愛いですね。                  ", 3);
		}

		if (tmsg == 7)
		{
			//txmsg("", 0);
			txmsg(" あの敵は連れて来れましたか?、     ", 1);
			txmsg(" 連れて来れなかった貴方は、        ", 2);
			txmsg(" そこの落とし穴から Let's dive!    ", 3);
		}

		if (tmsg == 8)
		{
			txmsg("そんな容易に", 1);
			txmsg("ヒントに頼るもんじゃないぜ", 2);
			txmsg("ほら、さっさと次行きな!!", 3);
		}

		if (tmsg == 9)
		{
			txmsg(" 正真正銘のファイナルステージ。    ", 1);
			txmsg(" クリアすれば遂にエンディング!!    ", 2);
			txmsg(" その土管から戻ってもいいんだぜ?   ", 3);
		}

		if (tmsg == 10)
		{
			txmsg(" 床が凍ってるから、すっごい滑るよ。",
				  1);
			//txmsg(" ", 2);
			//txmsg(" 　                      ", 3);
		}

		if (tmsg == 100)
		{
			txmsg("え？私ですか？ ", 0);
			txmsg("いやぁ、ただの通りすがりの", 2);
			txmsg("ヒントブロックですよ〜", 3);
			txmsg("決して怪しいブロックじゃないですよ", 5);
			txmsg("                          (…チッ)", 6);
		}

		setfont(16, 4);
	} // 2

	if (tmsgtype == 3)
	{
		xx[5] = (((15 - 1) * 1200 + 1500) / 100 - tmsgy / 100);
		if (xx[5] > 0)
		{
			setc0();
			fillrect(xx[1], xx[2] + tmsgy / 100, 360, xx[5]);
			setc1();
			drawrect(xx[1], xx[2] + tmsgy / 100, 360, xx[5]);
		}
	}
	#undef txmsg

} // ttmsg

// フォント変更 (Change font)
void setfont(int x, int y)
{
	SetFontSize(x);
	SetFontThickness(y);
}

void CreateGlobalTextCache()
{
	#define CACHE_GLOBAL_TEXT(text, c, sz, type) apGlobalTexts[text] = StringToSurface(text, c, sz, type)

	//Warp zone
	CACHE_GLOBAL_TEXT("WELCOME TO OWATA ZONE", GetColor(255, 255, 255), 20, DX_FONTTYPE_NORMAL);
	CACHE_GLOBAL_TEXT("1", GetColor(255, 255, 255), 20, DX_FONTTYPE_NORMAL);

	// Credits
    CACHE_GLOBAL_TEXT("制作・プレイに関わった方々", GetColor(255, 255, 255), 20, DX_FONTTYPE_NORMAL);
    CACHE_GLOBAL_TEXT("ステージ１　プレイ", GetColor(255, 255, 255), 20, DX_FONTTYPE_NORMAL);
    CACHE_GLOBAL_TEXT("先輩　Ｘ～Ｚ", GetColor(255, 255, 255), 20, DX_FONTTYPE_NORMAL);
    CACHE_GLOBAL_TEXT("ステージ２　プレイ", GetColor(255, 255, 255), 20, DX_FONTTYPE_NORMAL);
    CACHE_GLOBAL_TEXT("友人　willowlet ", GetColor(255, 255, 255), 20, DX_FONTTYPE_NORMAL);
    CACHE_GLOBAL_TEXT("ステージ３　プレイ", GetColor(255, 255, 255), 20, DX_FONTTYPE_NORMAL);
    CACHE_GLOBAL_TEXT("ステージ４　プレイ", GetColor(255, 255, 255), 20, DX_FONTTYPE_NORMAL);
    CACHE_GLOBAL_TEXT("友人２　ann ", GetColor(255, 255, 255), 20, DX_FONTTYPE_NORMAL);
    CACHE_GLOBAL_TEXT("ご協力", GetColor(255, 255, 255), 20, DX_FONTTYPE_NORMAL);
    CACHE_GLOBAL_TEXT("Ｔ先輩", GetColor(255, 255, 255), 20, DX_FONTTYPE_NORMAL);
    CACHE_GLOBAL_TEXT("Ｓ先輩", GetColor(255, 255, 255), 20, DX_FONTTYPE_NORMAL);
    CACHE_GLOBAL_TEXT("動画技術提供", GetColor(255, 255, 255), 20, DX_FONTTYPE_NORMAL);
    CACHE_GLOBAL_TEXT("Ｋ先輩", GetColor(255, 255, 255), 20, DX_FONTTYPE_NORMAL);
    CACHE_GLOBAL_TEXT("動画キャプチャ・編集・エンコード", GetColor(255, 255, 255), 20, DX_FONTTYPE_NORMAL);
    CACHE_GLOBAL_TEXT("willowlet ", GetColor(255, 255, 255), 20, DX_FONTTYPE_NORMAL);
    CACHE_GLOBAL_TEXT("プログラム・描画・ネタ・動画編集", GetColor(255, 255, 255), 20, DX_FONTTYPE_NORMAL);
    CACHE_GLOBAL_TEXT("ちく", GetColor(255, 255, 255), 20, DX_FONTTYPE_NORMAL);
    CACHE_GLOBAL_TEXT("プレイしていただき　ありがとうございました〜", GetColor(255, 255, 255), 20, DX_FONTTYPE_NORMAL);

	// Text boxes
	CACHE_GLOBAL_TEXT("テスト　hoge", GetColor(255, 255, 255), 20, DX_FONTTYPE_NORMAL);

	CACHE_GLOBAL_TEXT("ステージ 1 より", GetColor(255, 255, 255), 20, DX_FONTTYPE_NORMAL);
	CACHE_GLOBAL_TEXT("特殊的なものが増えたので", GetColor(255, 255, 255), 20, DX_FONTTYPE_NORMAL);
	CACHE_GLOBAL_TEXT("気をつけてくれよ〜", GetColor(255, 255, 255), 20, DX_FONTTYPE_NORMAL);
	CACHE_GLOBAL_TEXT("後、アイテムの一部を利用するかも…", GetColor(255, 255, 255), 20, DX_FONTTYPE_NORMAL);
	CACHE_GLOBAL_TEXT("                       ちく より", GetColor(255, 255, 255), 20, DX_FONTTYPE_NORMAL);

	CACHE_GLOBAL_TEXT("            ？が必要です ", GetColor(255, 255, 255), 20, DX_FONTTYPE_NORMAL);
	CACHE_GLOBAL_TEXT("                         m9(^Д^)", GetColor(255, 255, 255), 20, DX_FONTTYPE_NORMAL);

	CACHE_GLOBAL_TEXT("   別にコインに意味ないけどね ", GetColor(255, 255, 255), 20, DX_FONTTYPE_NORMAL);
	CACHE_GLOBAL_TEXT("                      (・ω・ )ﾉｼ", GetColor(255, 255, 255), 20, DX_FONTTYPE_NORMAL);

	CACHE_GLOBAL_TEXT("この先に隠しブロックがあります ", GetColor(255, 255, 255), 20, DX_FONTTYPE_NORMAL);
	CACHE_GLOBAL_TEXT("注意してください !!", GetColor(255, 255, 255), 20, DX_FONTTYPE_NORMAL);

	CACHE_GLOBAL_TEXT(" 前回よりも難易度を下げましたので", GetColor(255, 255, 255), 20, DX_FONTTYPE_NORMAL);
	CACHE_GLOBAL_TEXT(" 気楽にプレイしてください    ", GetColor(255, 255, 255), 20, DX_FONTTYPE_NORMAL);

	CACHE_GLOBAL_TEXT(" そこにいる敵のそばによると、      ", GetColor(255, 255, 255), 20, DX_FONTTYPE_NORMAL);
	CACHE_GLOBAL_TEXT(" 自分と一緒にジャンプしてくれます。", GetColor(255, 255, 255), 20, DX_FONTTYPE_NORMAL);
	CACHE_GLOBAL_TEXT("   可愛いですね。                  ", GetColor(255, 255, 255), 20, DX_FONTTYPE_NORMAL);

	CACHE_GLOBAL_TEXT(" あの敵は連れて来れましたか?、     ", GetColor(255, 255, 255), 20, DX_FONTTYPE_NORMAL);
	CACHE_GLOBAL_TEXT(" 連れて来れなかった貴方は、        ", GetColor(255, 255, 255), 20, DX_FONTTYPE_NORMAL);
	CACHE_GLOBAL_TEXT(" そこの落とし穴から Let's dive!    ", GetColor(255, 255, 255), 20, DX_FONTTYPE_NORMAL);

	CACHE_GLOBAL_TEXT("そんな容易に", GetColor(255, 255, 255), 20, DX_FONTTYPE_NORMAL);
	CACHE_GLOBAL_TEXT("ヒントに頼るもんじゃないぜ", GetColor(255, 255, 255), 20, DX_FONTTYPE_NORMAL);
	CACHE_GLOBAL_TEXT("ほら、さっさと次行きな!!", GetColor(255, 255, 255), 20, DX_FONTTYPE_NORMAL);

	CACHE_GLOBAL_TEXT(" 正真正銘のファイナルステージ。    ", GetColor(255, 255, 255), 20, DX_FONTTYPE_NORMAL);
	CACHE_GLOBAL_TEXT(" クリアすれば遂にエンディング!!    ", GetColor(255, 255, 255), 20, DX_FONTTYPE_NORMAL);
	CACHE_GLOBAL_TEXT(" その土管から戻ってもいいんだぜ?   ", GetColor(255, 255, 255), 20, DX_FONTTYPE_NORMAL);

	CACHE_GLOBAL_TEXT(" 床が凍ってるから、すっごい滑るよ。", GetColor(255, 255, 255), 20, DX_FONTTYPE_NORMAL);

	CACHE_GLOBAL_TEXT("え？私ですか？ ", GetColor(255, 255, 255), 20, DX_FONTTYPE_NORMAL);
	CACHE_GLOBAL_TEXT("いやぁ、ただの通りすがりの", GetColor(255, 255, 255), 20, DX_FONTTYPE_NORMAL);
	CACHE_GLOBAL_TEXT("ヒントブロックですよ〜", GetColor(255, 255, 255), 20, DX_FONTTYPE_NORMAL);
	CACHE_GLOBAL_TEXT("決して怪しいブロックじゃないですよ", GetColor(255, 255, 255), 20, DX_FONTTYPE_NORMAL);
	CACHE_GLOBAL_TEXT("                          (…チッ)", GetColor(255, 255, 255), 20, DX_FONTTYPE_NORMAL);

	#undef CACHE_GLOBAL_TEXT
}
