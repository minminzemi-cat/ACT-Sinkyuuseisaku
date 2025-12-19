#pragma once
#include "CCharacter.h"	//キャラクタークラス.
#include "CCamera.h"	//カメラクラス.

/**************************************************
*	エネミークラス.
**/
class CEnemy2
	: public CCharacter	//キャラクタークラスを継承.
{
public:
	CEnemy2();
	~CEnemy2();

	static const int E_SPD = 4;		//敵機の移動速度.
	static const int E_MAX = 1;		//敵機の最大数.
	static const int ES_TAMA = 100;		//のこ機の最大数.
	static const int ES_MAX = 100;		//のこ機の最大数.
	struct CHARA
	{
		int x;			//x座標.
		int y;			//y座標.
		int state;		//状態.
		int ExpAnimCnt;	//爆発アニメーションカウンタ.
	};
	VECTOR2 GetEPosition2() { return m_EPos2; }
	int* GetEnemyStetus2() { return m_EnemyState2; }
	void Update() override;
	void Draw(CCamera* pCamera) override;
	void syoukan(int x);
	void HIT(int i);
	void HIT2(int i);
	void ESHIT(int i);

	int C_SIZE = 64;	//キャラクタのサイズ.
	int encounter = 0;	//出現タイミング管理用カウンタ.
	int			m_tekiHP[E_MAX];
	int			m_esx[ES_MAX];
	int			m_esy[ES_MAX];
	bool		m_eshotFlag[ES_MAX];
	bool beside[ES_MAX];
private:
	int		    m_EnemyState2[E_MAX];	    //エネミーの生存確認
	VECTOR2     m_EPosition2[E_MAX];
	int         m_EnemyExpAnimCnt2[E_MAX];
	VECTOR2		m_EPos2;
};