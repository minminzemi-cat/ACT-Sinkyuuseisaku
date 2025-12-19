//#pragma once
//#include "CCharacter.h"	//キャラクタークラス.
//#include "CCamera.h"	//カメラクラス.
//
///**************************************************
//*	エネミークラス.
//**/
//class CEnemy
//	: public CCharacter	//キャラクタークラスを継承.
//{
//public:
//	CEnemy();
//	~CEnemy();
//
//	static const int E_SPD = 4;		//敵機の移動速度.
//	static const int E_MAX = 50;		//敵機の最大数.
//	static const int ES_TAMA = 100;		//のこ機の最大数.
//	static const int ES_MAX = 100;		//のこ機の最大数.
//	struct CHARA
//	{
//		int x;			//x座標.
//		int y;			//y座標.
//		int ExpAnimCnt;	//爆発アニメーションカウンタ.
//		VECTOR2 Position;
//	};
//
//	VECTOR2* GetEPosition() { return m_EPosition; }
//	int* GetEnemyStetus() { return m_EnemyState; }
//	
//	void Update() override;
//	void Draw(CCamera* pCamera) override;
//	void syoukan(int x);
//	void HIT(int i);
//
//	void SetImageEEX(CImage* sh) { EEXP_IMG = sh; }
//	void SetCH(CCharacter* sh) { m_CH = sh; }
//
//	CImage* EEXP_IMG;
//	CCharacter* m_CH;
//	int C_SIZE = 64;	//キャラクタのサイズ.
//	int encounter = 0;	//出現タイミング管理用カウンタ.
//	CHARA		m_Enemy[E_MAX];				//エネミー数
//	VECTOR2     m_EPosition[E_MAX];			//ポジション
//	int			m_tekiHP[E_MAX];			//敵の体力
//	int		    m_EnemyState[E_MAX];	    //エネミーの生存確認
//	int			m_esx[ES_MAX];				//
//	int			m_esy[ES_MAX];				//
//	int         m_EnemyExpAnimCnt[E_MAX];	//
//	bool		m_eshotFlag[ES_MAX];		//エネミーショット
//private:
//};