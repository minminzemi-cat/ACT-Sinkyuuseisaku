#pragma once
#include "CCharacter.h"	//キャラクタークラス.
#include "CCamera.h"	//カメラクラス.
#include "MyMath.h"	//カメラクラス.
#include <cmath>
#include<vector>

#pragma comment( lib, "msimg32.lib" )	//指定色を透過して描画で使用する.
//半透明の描画でも使用

//=======================================
//クラス
//=====================================
class CBoss 
	: public CCharacter	//キャラクタークラスを継承.
{

public:
	//定数宣言

	static const int BS_SPD = 6;		//bossの玉の速度
	static const int BS_MAX = 3;		//bossの玉の数
	static const int B_SPD = 1;			//bossの移動速度
	static const int B_MAX = 1;			//bossの最大数
	 int B_HP = 200;			//ボスのHP


	 enum enBossState
	 {
		 Leving,	//生きている
		 Ded,		//死んでる


	 };




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

	//画像読み込み
	void SetImageBoss(CImage* pImg) {m_bossIMG = pImg; }
	void SetImageBOSSHand(CImage* pImg) { m_pbossHandImg = pImg; }
	void SetImageShot(CImage* pImg) { m_pbossshotImg = pImg; }
	
	//爆発の画像読込
	void SetImageBom(CImage* pImg) { m_pbossBomImg = pImg; }

public:

	//画像の定義
	CImage* m_bossIMG;
	CImage* m_pbossHandImg;
	CImage* m_pbossshotImg;
	CImage* m_pbossBomImg;

	//初期化（リセット）
	void InitializeGame();


	//計算するための関数

	// --- 自機を遅くするWay弾発射 ---
	void SlowWayShot(int slowway, float angleRangeRad, float speed);

	// --- Way弾発射 ---
	void Way(int way, float angleRangeRad, float speed);

	//-----ばらまき弾--------
	void bara(int num, float speed);





	//自機をおそくするway
	void SlowUpdate();

	//普通のway
	void WayUpdate();

	//ボスの一部から発射される、ばらまき
	void BaraUpdate();

	
	//ボスが左右に動いたりするための処理

	void Update() override;

	//描画・・・結合するにあたり、ボスの一部だけでも描画する
	void Draw(CCamera* pCamera) override;
	
	

	//ボス本体を描画する関数
	void ZDraw(CCamera* pCamera);

	//ボスの一部の描画
	void XDraw(CCamera* pCamera);

	//ボスの一部の描画
	void RDraw(CCamera* pCamera);
	

	CHARA m_Boss;

	//ボスの一部
	CHARA m_Boss_bui;


	enBossHurase m_BossHurase;


	int bosstime = 0;

	int x;		//x座標
	int y;		//ｙ座標
	int state;	//状態
	int ExpAnimCnt;					//爆発アニメーションカウンタ
	float fireInterval = 500;		// 発射間隔（mili秒）
	float BarafireInterval = 450;	// 発射間隔（mili秒）
	float fireTimer = 0.0f;			// 発射間隔（mili秒）
	float BarafireTimer = 0.0f;		// 発射間隔（mili秒）

	
	float m_bsx[BS_MAX];
	float m_bsy[BS_MAX];

	bool		m_bshotFlag[BS_MAX];

	int D;

	VECTOR2 shotpos;


	void HIT();

	//ベクトル２はx,y座標をまとめて管理するためのもの
	VECTOR2* BossGetPosition() { return m_BossPosition; }

	VECTOR2* BossBuiGetPosition() { return m_Boss_BuiPosition; }

    
    int m_bossState; // ボスの状態を管理するメンバ変数
	//Vector2とはX, Y の2成分で構成される情報である


	//荒田先生のコードに書いてあったもの
	std::vector<CBoss::SlowWay> SlowWayShots;

	std::vector<CBoss::WayShot> WayShots;

	std::vector<CBoss::Baramaki> BaraShots;





	//ボスのHPゲージを作らないといけない
	CImage* m_pBossGazi;

	int m_RightLeft;


	bool m_BossState;

	int m_Utime;
    
    
	//ボスのポジション　x,y座標を同時に
	VECTOR2* m_BossPosition; // m_BossPosition を定義


	//ボスの一部　x,y座標を同時に
	VECTOR2* m_Boss_BuiPosition;//m_Boss_BuiPosition を定義

};