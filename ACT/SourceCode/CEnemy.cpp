#include "CEnemy.h"
#include "CGame.h"
#include <cmath> 


CEnemy::CEnemy()
	: encounter(0)
	, D(0)
{
	for (int i = 0; i < E_MAX; i++)
	{
		m_EnemyState[i] = enCharaState::Standby;
		m_EPosition[i].x = -655;
		m_EPosition[i].y = -C_SIZE;
	    m_EnemyExpAnimCnt[i] = 0;
	}
	for (int i = 0; i < ES_MAX; i++)
	{
		m_esx[i] = WND_W;
		m_esy[i] = WND_H;
		m_eshotFlag[i] = false;
		m_esvx[i] = 0.0f;
		m_esvy[i] = 0.0f;
	}
	playerX = 0.0f;
	playerY = 0.0f;
	enemyX = 0.0f;
	enemyY = 0.0f;
	m_Killcnt = 0;
	SP = 0;
}

CEnemy::~CEnemy()
{
}

// Ž©‹@‘_‚¢’e‚Ì”­ŽËŠÖ”
void CEnemy::shootPlayer(float targetX, float targetY)
{
	for (int i = 0; i < ES_MAX; i++) {
		if (m_eshotFlag[i] == false) {

			float startX = enemyX;
			float startY = enemyY;

			float dx = targetX - startX;
			float dy = targetY - startY;

			// ’e‚ÌˆÚ“®‘¬“x‚Ì‘¬‚³
			const float BULLET_SPEED = 4.0f;

			//Šp“x
			float angle = atan2(dy, dx);

			// ‘¬“xŒvŽZ
			m_esvx[i] = cos(angle) * BULLET_SPEED;
			m_esvy[i] = sin(angle) * BULLET_SPEED;

			m_esx[i] = startX;
			m_esy[i] = startY;

			m_eshotFlag[i] = true;

			break;
		}
	}
}

void CEnemy::Update()
{

	//“G‚ÌˆÚ“®ƒƒWƒbƒN

	for (int i = 0; i < E_MAX; i++)
	{
		if (m_EnemyState[i] != enCharaState::Living) continue;

		if (m_EPosition[i].y < WND_H / 2 + 120)
		{
			m_EPosition[i].y += 2;	// ‰º‚ÖˆÚ“®
		}
		else
		{
			if (m_EPosition[i].x < WND_W / 2 - 32) {
				m_EPosition[i].x -= E_SPD;	// ¶‚ÖˆÚ“®
			}
			else {
				m_EPosition[i].x += E_SPD;	// ‰E‚ÖˆÚ“®
			}
		}

		if (m_EPosition[i].x > WND_W || m_EPosition[i].y > WND_H) {
			m_EnemyState[i] = enCharaState::Dead;
		}
	}

	//“G‹@‚Ì’e‚Ì”­ŽË

	for (int i = 0; i < E_MAX; i++)
	{
		if (m_EnemyState[i] == enCharaState::Living) {

			
			if (m_EPosition[i].y > C_SIZE && encounter % 60 == 0) {

				
				enemyX = m_EPosition[i].x;
				enemyY = m_EPosition[i].y;

				// Ž©‹@‘_‚¢’e‚ð”­ŽË
				shootPlayer(playerX, playerY);
			}
		}
	}

	//“G‹@‚Ì’e‚ÌˆÚ“®

	for (int i = 0; i < ES_MAX; i++) {
		if (m_eshotFlag[i] == true) {

			
			m_esx[i] += m_esvx[i];
			m_esy[i] += m_esvy[i];

			//‰æ–ÊŠO‚Éo‚½‚ç’e‚ðÁ‚·
			if (m_esx[i] < -C_SIZE || m_esx[i] > WND_W + C_SIZE ||
				m_esy[i] < -C_SIZE || m_esy[i] > WND_H + C_SIZE) {

				m_esx[i] = (float)WND_W;
				m_esy[i] = (float)WND_H;
				m_eshotFlag[i] = false;
			}
		}
	}


	
	encounter++;

	
	if (encounter > 1850) {
		encounter = 0;
	}

	if (encounter == 60 || encounter == 90 || encounter == 60*2) {
		syoukan(0);
	}

	if (encounter == 60*3 || encounter == (60*3)+30 || encounter == 60*4) {
		syoukan(480-64);
	}
	
	if (encounter == 60 * 6)
	{
		syoukan( (WND_W/2) - (64/2) );
	}
	if (encounter == (60 * 6)+30)
	{
		syoukan((WND_W / 2) - (64 / 2)+30);
	}
	if (encounter == (60 * 6) + 30)
	{
		syoukan((WND_W / 2) - (64 / 2)-30);
	}

}

void CEnemy::Draw(CCamera* pCamera)
{
	

	for (int i = 0; i < E_MAX; i++)
	{
		if (m_EnemyState[i]==enCharaState::Living)
		{

			m_FrameSplit.w = 64;
			m_FrameSplit.h = 64;
			m_FrameSplit.x = 0;
			m_FrameSplit.y = 64*2;


			m_pImg->TransBlt(
				m_EPosition[i].x,
				m_EPosition[i].y,
				m_FrameSplit.w,
				m_FrameSplit.h,
				m_FrameSplit.x,
				m_FrameSplit.y);


		}

			else if (m_EnemyState[i] == enCharaState::Deading)
			{
				EEXP_IMG->TransBlt(
					m_EPosition[i].x,
					m_EPosition[i].y,
					64,
					64,

					(m_EnemyExpAnimCnt[i] % 8) * 64,
					(m_EnemyExpAnimCnt[i] / 8) * 64);
			}
			if (m_EnemyState[i] == enCharaState::Deading)
			{
				m_EnemyExpAnimCnt[i]++;
				if (m_EnemyExpAnimCnt[i] >= 30)
				{
					m_EnemyState[i] = enCharaState::Dead;
				}
			}
	}


	//“G’e‚Ì•`‰æ
	for (int i = 0; i < ES_MAX; i++) {
		if (m_eshotFlag[i] == true) {
			D++;
			m_FrameSplit.w = 32;
			m_FrameSplit.h = 32;
			m_FrameSplit.x = 64;
			m_FrameSplit.y = 64*2;

			VECTOR2 bulletPos;
			bulletPos.x = m_esx[i];
			bulletPos.y = m_esy[i]; 

			
			VECTOR2 DispPos = pCamera->CalcToPositionInCamera(&bulletPos, &m_FrameSplit);

			m_pImg->TransSpinAlBlt(
				DispPos.x,
				DispPos.y,
				m_FrameSplit.w,
				m_FrameSplit.h,
				m_FrameSplit.x,
				m_FrameSplit.y,
				64, 64,
				D, 200);
		}
	}
}


void CEnemy::syoukan(int x)
{
	for (int i = 0; i < E_MAX; i++)
	{
	
		if (m_EnemyState[i] == enCharaState::Standby)
		{
			m_EPosition[i].x = x;
			m_EPosition[i].y = -C_SIZE;
			m_EnemyState[i] = enCharaState::Living;
			m_EnemyExpAnimCnt[i] = 0;
			break;
		}
	}
	
}

void CEnemy::HIT(int i)
{

	m_EnemyState[i] = enCharaState::Deading;
	m_Killcnt += 1;
	SP += 1;
	CSoundManager::PlaySE(CSoundManager::enList::SE_Ken);

	

}

void CEnemy::HIT2(int i)
{

	for (int i = 0; i < E_MAX; i++)
	{
		if (m_EnemyState[i] == enCharaState::Living)
		{
			m_EnemyState[i] = enCharaState::Deading;
		}
	}

	
	
}

void CEnemy::ESHIT(int i)
{
	for (int i = 0; i < ES_MAX; i++)
	{
		m_eshotFlag[i] = false;
	}

	
}
