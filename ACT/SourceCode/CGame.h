#pragma once
#include <Windows.h>
#include "Global.h"
#include "MyMacro.h"		//マクロ.
#include "CImage.h"			//イメージクラス.
#include "CPlayer.h"		//プレイヤークラス.
#include "CPlayerShot.h"		//プレイヤークラス.
#include "CEnemy.h"			//エネミークラス.
#include "CEnemy2.h"			//エネミークラス.
#include "CEnemy3.h"			//エネミークラス.
#include "CBoss.h"			//エネミークラス.
#include"CCharacter.h"
#include "Excalibur.h"			//エネミークラス.
#include "CStage.h"			//ステージクラス.
#include "CCamera.h"		//カメラクラス.

#include"CTitle.h"

#include"CScore.h"

#include "GameOver.h"		//カメラクラス.
#include "Ending.h"		//カメラクラス.
#include "Result.h"		//カメラクラス.
#include "Hitjudgment.h"

/**************************************************
*	ゲームクラス.
**/

class CGame
	:CCharacter
{
public:
	//---------------------------------------
	//	定数宣言.
	//---------------------------------------
	static const int C_SIZE = 64;	//キャラクターサイズ.
	static const int P_SPD = 4;		//プレイヤー移動速度.

	//---------------------------------------
	//	列挙型宣言.
	//---------------------------------------

	//シーン列挙型.
	enum enScene
	{
		Title,		//タイトル.
		GameMain,	//ゲーム中.
		GameOver,	//ゲームオーバー.
		Ending,		//エンディング.
		Result,
	};

	//---------------------------------------
	//	構造体宣言.
	//---------------------------------------
	//キャラクター構造体.


public:
	CGame();	//コンストラクタ.
	CGame( GameWindow* pGameWnd );//コンストラクタ(引数あり).
	~CGame();	//デストラクタ.

	//初期化(リセット)関数.
	void InitializeGame();
	//構築関数.
	bool Create();
	//破棄関数.
	void Destroy();
	//更新関数(キー入力や動作処理を行う).
	void Update();
	//描画関数(画像の表示処理を行う).
	void Draw();

	//ウィンドウを閉じているか確認.
	BOOL IsWindowClosed() const { return m_pGameWnd->isWndClose; }
	//FPSを取得.
	DWORD GetFPS() const { return m_pGameWnd->dwFPS; }
	//バックバッファを取得.
	HDC GetScreenDC() const { return m_pGameWnd->hScreenDC; }
	//ウィンドウハンドルを取得.
	HWND GetWnd() const { return m_pGameWnd->hWnd; }

	int GetSene() { return m_scene; }
private:

	CHitjudgment* m_Hantei;
	GameWindow*	m_pGameWnd;		//ゲームウィンドウ構造体.
	HDC			m_hMemDC;		//メモリデバイスコンテキスト.
	HDC			m_hWorkDC;		//作用用DC.
	HBITMAP		m_hWorkBmp;		//作業用BITMAP.
	HDC			m_hWorkDC2;		//作用用DC.
	HBITMAP		m_hWorkBmp2;		//作業用BITMAP.
	HFONT		m_hFont;		//フォントハンドル.
	CImage*		m_pBackImg;		//背景画像.

	//スコア
	CImage* m_ScoreImg;
	
	//タイトル

	CImage* m_pTitleImg;

	CImage* m_pKennImg;

	CImage*     m_pOverImg;
	CImage*     m_pEndingImg;
	CImage*     m_pResultImg;
	CImage*     m_pRankImg;
	CImage*		m_pCharaImg;	//キャラクター画像.
	CImage*     m_pPLeftImg;	//キャラクター残基.
	CImage*     m_pEExprotionImg;
	CImage*     m_pExprotionImg;
	CImage*     m_pPShotImg;    //プレイヤーショット
	CImage*     m_pBShotImg;    //プレイヤーボスショット
	CImage*		m_pBomSetImg;	//ボムセット
	CImage*		m_pKenImg;	    //剣
	CImage*     m_pSPMoveImg;   //プレイヤー必殺
	CImage*     m_pSPImg;       //プレイヤー必殺
	CImage*		m_pSPGeagImg;   //必殺ゲージ
	CImage*		m_pEnemyImg;	//敵画像.
	CImage*     m_pEnemy2Img;	//敵画像.

	//ボス本体
	CImage*		m_pbossImg;
	//ボスの一部
	CImage*		m_pbossHandImg;

	//ボスの弾
	CImage* m_pbossWayshotImg;
	CImage* m_pbossSlowshotImg;
	CImage* m_pbossbuiImg;

	//ボスの爆発
	CImage* m_pbossBomImg;

	//ボスの体力ゲージ
	CImage* m_pbossGageImg;


	CImage*		m_pPlayerImg;	//プレイヤー画像.
	CImage*		m_pStageImg;	//ステージ画像.
	CImage*     m_pscoreImg;	//スコア画像.
	

	//-----自機-----.
 enCharaState		m_Player;
	CPlayer*	m_pPlayer;	//プレイヤー.
	PSHOT*      m_ppshot;
	Exculibur* m_Exc;
	CCharacter* m_CH;
	//-----敵機-----.
	CEnemy*		m_pEnemy;	//エネミー.
	CEnemy2*	m_pEnemy2;
	CEnemy3* m_pEnemy3;


	CBoss* m_pBoss;


	//-----ステージ-----.
	CStage*		m_pStage;
	//----- カメラ ----.
	CCamera* m_pCamera;		//カメラ.



	CTitle* m_pTitle;

	CTitle* m_TitleSword;


	CScore* m_Score;

	int score;
	
	CGameOver* m_GameOver;
	CEnding* m_Ending;
	CResult* m_result;
	enScene  m_scene;
	CGame* m_cgame;
	
};



//矩形同士の当たり判定.
bool CollisionDetection(
	int Ax, int Ay, int Aw, int Ah,		//矩形Aのx,y座標と幅高さ.
	int Bx, int By, int Bw, int Bh );	//矩形Bのx,y座標と幅高さ.

bool collisionSpher(
	int r1x, int r1y, int Aw, int Ah,			//矩形Aの座標と高さ
	int r2x, int r2y, int Bw, int Bh);