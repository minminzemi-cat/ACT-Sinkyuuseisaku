#include "CEnemy.h"
#include "CGame.h"
#include "CEnemy3.h"


CEnemy3::CEnemy3()
	: encounter(0)
{
	for (int i = 0; i < E_MAX; i++)
	{
		m_Enemy[i].state = enCharaState::Dead; // 全員「死亡」状態にしておく
		m_Enemy[i].x = -60055;
		m_Enemy[i].y = -C_SIZE;
		m_Enemy[i].ExpAnimCnt = 0;
	}
	for (int i = 0; i < ES_MAX; i++)
	{
		m_esx[i] = WND_W;
		m_esy[i] = WND_H;
		m_eshotFlag[i] = false;
	}
	

}

CEnemy3::~CEnemy3()
{
}
void CEnemy3::Update()
{
	for (int i = 0; i < E_MAX; i++)
	{
		m_Enemy[i].y += 1;	// 下へ移動
		if (m_Enemy[i].x <= 0) {
			beside[i] = true;
		}

		if (m_Enemy[i].x > WND_W - 32) {
			beside[i] = false;
		}
		if (beside[i] == false) {
			m_Enemy[i].x -= E_SPD;	// 右へ移動
		}
		else if (beside[i] == true) {
			m_Enemy[i].x += E_SPD;	// 左へ移動
		}
		if (m_Enemy[i].x > WND_W || m_Enemy[i].y > WND_H) {
			m_Enemy[i].state = enCharaState::Dead;
		}
	}

	
	//敵機の動作.
	for (int i = 0; i < E_MAX; i++)
	{
		if (m_Enemy[i].state == enCharaState::Living) {
			for (int i = 0; i < ES_MAX; i++) {

				if (m_eshotFlag[i] == false) {

					m_esx[i] = m_Enemy[i].x;
					m_esy[i] = m_Enemy[i].y;
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

void CEnemy3::Draw(CCamera* pCamera)
{
	for (int i = 0; i < E_MAX; i++)
	{
		m_FrameSplit.w = 64;
		m_FrameSplit.h = 64;
		m_FrameSplit.x = 128;
		m_FrameSplit.y = 0;

		VECTOR2 DispPos = pCamera->CalcToPositionInCamera(&m_Position, &m_FrameSplit);
		//敵の表示
		m_pImg->TransBlt(
			m_Enemy[i].x,
			m_Enemy[i].y,
			//vertical = rand() % (480 - 128),
			m_FrameSplit.w,
			m_FrameSplit.h,
			m_FrameSplit.x,
			m_FrameSplit.y);
	}
	for (int i = 0; i < ES_MAX; i++) {
		if (m_eshotFlag[i] == true) {
			m_FrameSplit.w = 192;
			m_FrameSplit.h = 64;
			m_FrameSplit.x = 64;
			m_FrameSplit.y = 128;

			VECTOR2 bulletPos;
			bulletPos.x = m_esx[i];
			bulletPos.y = m_esy[i];

			VECTOR2 DispPos = pCamera->CalcToPositionInCamera(&bulletPos, &m_FrameSplit);

			m_pImg->TransBlt(
				DispPos.x+64,
				DispPos.y,
				m_FrameSplit.w,
				m_FrameSplit.h,
				m_FrameSplit.x,
				m_FrameSplit.y);
		}
	}
}
void CEnemy3::syoukan(int x)
{
	for (int i = 0; i < E_MAX; i++)//敵機の数だけ処理する.
	{
		if (m_Enemy[i].state == enCharaState::Dead) {
			m_Enemy[i].x = x;	//任意の場所に出現
			m_Enemy[i].y = -32;
			m_Enemy[i].state = enCharaState::Living;	//死亡中
			m_Enemy[i].ExpAnimCnt = 0;
			beside[i] = false;
			break;
		}
	}
}

