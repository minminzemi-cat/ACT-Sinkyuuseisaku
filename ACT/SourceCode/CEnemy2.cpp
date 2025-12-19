#include "CEnemy.h"
#include "CGame.h"
#include "CEnemy2.h"


CEnemy2::CEnemy2()
	: encounter(0)
{
	for (int i = 0; i < E_MAX; i++)
	{
		m_EnemyState2[i] = enCharaState::Dead; // 全員「死亡」状態にしておく
		m_EPosition2[i].x = -60055;
		m_EPosition2[i].y = -C_SIZE;
		m_EnemyExpAnimCnt2[i] = 0;
	}
	for (int i = 0; i < ES_MAX; i++)
	{
		m_esx[i] = WND_W;
		m_esy[i] = WND_H;
		m_eshotFlag[i] = false;
	}

}

CEnemy2::~CEnemy2()
{
}
void CEnemy2::Update()
{
	for (int i = 0; i < E_MAX; i++)
	{
		m_EPosition2[i].y += 1;	// 下へ移動
		if (m_EPosition2[i].x > WND_W - 32) {
			beside[i] = true;
		}

		if (m_EPosition2[i].x < 0) {
			beside[i] = false;
		}
		if (beside[i] == true) {
			m_EPosition2[i].x -= E_SPD;	// 右へ移動
		}
		else {
			m_EPosition2[i].x += E_SPD;	// 左へ移動
		}
		if (m_EPosition2[i].x > WND_W || m_EPosition2[i].y > WND_H) {
			m_EnemyState2[i] = enCharaState::Dead;
		}
	}
	
	//敵機の動作.
	for (int i = 0; i < E_MAX; i++)
	{
		if (m_EnemyState2[i] == enCharaState::Living) {
			for (int i = 0; i < ES_MAX; i++) {

				if (m_eshotFlag[i] == false) {

					m_esx[i] = m_EPosition2[i].x;
					m_esy[i] = m_EPosition2[i].y;
					m_eshotFlag[i] = true;
					break;
				}

			}

		}
	}
	for (int i = 0; i < ES_MAX; i++) {
		if (m_eshotFlag[i] == true) {
			m_esy[i] += 6;
			if (m_esy[i] > WND_H) {
				m_esx[i] = WND_W;
				m_esy[i] = WND_H;
				m_eshotFlag[i] = false;
			}
		}
	}
	encounter++;
	if (encounter == 60) {//encounterの数値を変えれば好きなタイミングで出現可能
		syoukan(WND_W / 2);//かっこの中身を変えれば好きな場所に出現可能
	}
}

void CEnemy2::Draw(CCamera* pCamera)
{
	for (int i = 0; i < E_MAX; i++)
	{
		if (m_EnemyState2[i] == enCharaState::Living)
		{
			m_FrameSplit.w = 64;
			m_FrameSplit.h = 64;
			m_FrameSplit.x = 0;
			m_FrameSplit.y = 64*3;

			m_EPos2.x = m_EPosition2[i].x;
			m_EPos2.y = m_EPosition2[i].y;

			VECTOR2 DispPos = pCamera->CalcToPositionInCamera(&m_EPos2, &m_FrameSplit);
			//敵の表示
			m_pImg->TransBlt(
				m_EPosition2[i].x,
				m_EPosition2[i].y,
				//vertical = rand() % (480 - 128),
				m_FrameSplit.w,
				m_FrameSplit.h,
				m_FrameSplit.x,
				m_FrameSplit.y);
		}
	}
	for (int i = 0; i < ES_MAX; i++)
	{
		if (m_EnemyState2[i] == enCharaState::Living)
		{
			if (m_eshotFlag[i] == true) 
			{
				m_FrameSplit.w = 128;
				m_FrameSplit.h = 64;
				m_FrameSplit.x = 64;
				m_FrameSplit.y = 64*3;

				VECTOR2 bulletPos;
				bulletPos.x = m_esx[i];
				bulletPos.y = m_esy[i];

				VECTOR2 DispPos = pCamera->CalcToPositionInCamera(&bulletPos, &m_FrameSplit);

				m_pImg->TransBlt(
					DispPos.x + 44,
					DispPos.y,
					m_FrameSplit.w,
					m_FrameSplit.h,
					m_FrameSplit.x,
					m_FrameSplit.y);
			}
		}
	}
}
void CEnemy2::syoukan(int x)
{
	for (int i = 0; i < E_MAX; i++)//敵機の数だけ処理する.
	{
		if (m_EnemyState2[i]== enCharaState::Dead) {
			m_EPosition2[i].x = x;	//任意の場所に出現
			m_EPosition2[i].y = -32;
			m_EnemyState2[i] = enCharaState::Living;	//死亡中
			m_EnemyExpAnimCnt2[i] = 0;
			break;
		}
	}
}

void CEnemy2::HIT(int i)
{
	m_EnemyState2[i] = enCharaState::Deading;
	m_Killcnt += 1;
	CSoundManager::PlaySE(CSoundManager::enList::SE_Ken);

}

void CEnemy2::HIT2(int i)
{

	for (int i = 0; i < E_MAX; i++)
	{
		if (m_EnemyState2[i] == enCharaState::Living)
		{
			m_EnemyState2[i] = enCharaState::Deading;
		}
	}

}

void CEnemy2::ESHIT(int i)
{
	for (int i = 0; i < ES_MAX; i++)
	{
		m_eshotFlag[i] = false;
	}
}
