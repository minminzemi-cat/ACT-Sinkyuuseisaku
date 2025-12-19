#pragma once
#include "CCharacter.h"	//キャラクタークラス.
#include "CCamera.h"	//カメラクラス.
#include "MyMath.h"	//カメラクラス.
#include <cmath>
#include <vector>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
/**************************************************
*	エネミークラス.
**/
class CEnemy
	: public CCharacter	//キャラクタークラスを継承.
{
public:
	CEnemy();
	~CEnemy();

	

	static const int E_SPD = 4;		//敵機の移動速度.
	static const int E_MAX = 100;	//敵機の最大数.
	static const int ES_MAX = 50;	//敵弾の最大数.

	struct CHARA
	{
		int x;			//x座標.
		int y;			//y座標.
		int state;		//状態.
		int ExpAnimCnt;	//爆発アニメーションカウンタ.
	};

	struct Bullet {
		float x, y;
		float vx, vy;
	};

	void Update() override;
	void Draw(CCamera* pCamera) override;
	void syoukan(int x);
	void HIT(int i);
	void HIT2(int i);
	void ESHIT(int i);

	void shootPlayer(float targetX, float targetY);
	void SetImageEEX(CImage* sh) { EEXP_IMG = sh; }
	VECTOR2 GetbulletPos() { return bulletPos; }
	VECTOR2* GetEPosition() { return m_EPosition; }
	int* GetEnemyStetus() { return m_EnemyState; }

	std::vector<Bullet> bullets;

	int SetPosX(int x) { return m_Position.x = x; }
	int SetPosY(int y) { return m_Position.y = y; }
	int C_SIZE = 64;	//キャラクタのサイズ.
	int encounter = 0;	//出現タイミング管理用カウンタ.
	int			m_tekiHP[E_MAX];

	float		m_esx[ES_MAX];	
	float		m_esy[ES_MAX];		
	float m_esvx[ES_MAX];
	float m_esvy[ES_MAX];
	float enemyX = 0.0f;
	float enemyY = 0.0f;
	float playerX = 0.0f;
	float playerY = 0.0f;

	bool		m_eshotFlag[ES_MAX];


private:
	VECTOR2 bulletPos;
	CImage*		EEXP_IMG;
	CImage*     m_pEshotImg;
	int		    m_EnemyState[E_MAX];	    //エネミーの生存確認
	VECTOR2     m_EPosition[E_MAX];
	int         m_EnemyExpAnimCnt[E_MAX];	//
	int D;


};