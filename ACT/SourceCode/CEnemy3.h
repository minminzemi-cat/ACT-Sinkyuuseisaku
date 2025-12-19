#pragma once
#include "CCharacter.h"	//キャラクタークラス.
#include "CCamera.h"	//カメラクラス.

/**************************************************
*	エネミークラス.
**/
class CEnemy3
	: public CCharacter	//キャラクタークラスを継承.
{
public:
	CEnemy3();
	~CEnemy3();

	static const int E_SPD = 4;		//敵機の移動速度.
	static const int E_MAX = 100;		//敵機の最大数.
	static const int ES_TAMA = 100;		//のこ機の最大数.
	static const int ES_MAX = 100;		//のこ機の最大数.
	struct CHARA
	{
		int x;			//x座標.
		int y;			//y座標.
		int state;		//状態.
		int ExpAnimCnt;	//爆発アニメーションカウンタ.
	};

	void Update() override;
	void Draw(CCamera* pCamera) override;
	void syoukan(int x);
	int C_SIZE = 64;	//キャラクタのサイズ.
	int encounter = 0;	//出現タイミング管理用カウンタ.
	CHARA		m_Enemy[E_MAX];
	int			m_tekiHP[E_MAX];
	int			m_esx[ES_MAX];
	int			m_esy[ES_MAX];
	bool		m_eshotFlag[ES_MAX];
	bool beside[E_MAX];
private:
};
