#pragma once
#include<Windows.h>
#include"Global.h"
#include "CSound.h"		//サウンドクラス
#include"CImage.h"
#include<vector>

#pragma comment( lib, "msimg32.lib" )	//指定色を透過して描画で使用する.
//半透明の描画でも使用

//=======================================
//クラス
//=====================================
class CBoss {
public:
	//定数宣言

	static const int BS_SPD = 6;		//bossの玉の速度
	static const int BS_MAX = 3;		//bossの玉の数
	static const int B_SPD = 1;			//bossの移動速度
	static const int B_MAX = 1;			//bossの最大数
	 int B_HP = 200;			//ボスのHP

	 //ボスの一部を降らせて、空中で止めてバラマキ弾を打つ
	 enum enBossHurase
	 {
		 taiki,		//待機
		 hurase,	//降らせます
		 tome,		//空中で止めます
		 utima,		//ばらまき撃ちます
		 modorima	//戻ります

	 };




public:
	CBoss();	//コンストラクタ
	CBoss(GameWindow* pGameWnd);//コンストラクタ（引数あり）
	~CBoss();	//デストラクタ

	//キャラクター構造体
	struct CHARA
	{
		int x;	//x座標
		int y;	//ｙ座標
	};
	
	//自機を遅くするway弾の構造体
	struct SlowWay {
		float qx, qy;
		float vx, vy;
	};


	// way弾の構造体
	struct WayShot {
		float  wx, wy;   // 位置
		float vx, vy;   // 速度 (単位: 座標/秒)
	};

	// ばらまき弾の構造体
	struct Baramaki {
		float zx, zy;   // 位置
		float vx, vy; // 速度 (座標/秒)
	};
	void SetImageBoss(CImage* pImg) {m_bossIMG = pImg; }
	void SetImageBOSSHand(CImage* pImg) { m_subboss = pImg; }
public:

	CImage* m_bossIMG;
	CImage* m_subboss;

	//初期化（リセット）
	void InitializeGame();

	// --- 自機を遅くするWay弾発射 ---
	void SlowWayShot(int slowway, float angleRangeRad, float speed);

	// --- Way弾発射 ---
	void Way(int way, float angleRangeRad, float speed);

	//-----ばらまき弾--------
	void bara(int num, float speed);

	//自機をおそくするway描画
	void display();

	//普通のway描画
	void WayDraw();

	//ボスの一部から発射される、ばらまき描画
	void BaraDraw();

	

	//画像を読み込ませるための関数
	void Init(HDC hScreenDC, HDC hMemDC, HDC hWorkDC);

	//ボスが左右に動いたりするための処理
	void Update();

	//描画・・・結合するにあたり、ボスの一部だけでも描画する
	void Draw(HDC m_hMemDC);

	//ボス本体を描画する関数
	void ZDraw(HDC m_hMemDC);
	

	CHARA m_Boss;

	//ボスの一部
	CHARA m_Boss_bui;


	enBossHurase m_BossHurase;


	int x;	//x座標
	int y;	//ｙ座標
	int state;//状態
	int ExpAnimCnt;	//爆発アニメーションカウンタ
	float fireInterval = 500; // 発射間隔（mili秒）
	float BarafireInterval = 450; // 発射間隔（mili秒）
	float fireTimer = 0.0f;
	float BarafireTimer = 0.0f;

	std::vector<CBoss::SlowWay> SlowWayShots;

	std::vector<CBoss::WayShot> WayShots;

	std::vector<CBoss::Baramaki> BaraShots;

	//ボスの一部
	CImage* m_pBoss_buiImg;

	//ボス本体
	CImage* m_pZBossImg;

	//ボスのHPゲージを作らないといけない
	CImage* m_pBossGazi;

	int m_RightLeft;
};