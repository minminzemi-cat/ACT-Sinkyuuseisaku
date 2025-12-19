//#include "CEnemy.h"
//#include "CGame.h"
//
//
//CEnemy::CEnemy()
//	: encounter(0)
//
//{
//	for (int i = 0; i < E_MAX; i++)
//	{
//		m_EnemyState[i]= enCharaState::Standby; // ‘SˆõuŽ€–Svó‘Ô‚É‚µ‚Ä‚¨‚­
//		m_EPosition[i].x = -655;
//		m_EPosition[i].y = -C_SIZE;
//		m_Killcnt = 0;
//		m_EnemyExpAnimCnt[i] = 0;
//	}
//}
//
//CEnemy::~CEnemy()
//{
//}
//void CEnemy::Update()
//{
//	for (int i = 0; i < E_MAX; i++)
//	{
//
//		if (m_EnemyState[i] != enCharaState::Living) continue; {
//
//			if (m_EPosition[i].y < WND_H / 2 + 120)
//			{
//				m_EPosition[i].y += E_SPD;	// ‰º‚ÖˆÚ“®
//			}
//			else
//			{
//				if (m_EPosition[i].x < WND_W / 2 - 32) {
//					m_EPosition[i].x -= E_SPD;	// ¶‚ÖˆÚ“®
//				}
//				else {
//					m_EPosition[i].x += E_SPD;	// ‰E‚ÖˆÚ“®
//				}
//			}
//		}
//
//		if (m_EPosition[i].x > WND_W || m_EPosition[i].y > WND_H) {
//			m_EnemyState[i] = enCharaState::Deading;
//		}
//	}
//
//	encounter++;
//	if (encounter == 60 || encounter == 80 || encounter == 100) {
//		syoukan(0);
//
//	}
//	if (encounter == 160 || encounter == 180 || encounter == 200) {
//		syoukan(WND_W - C_SIZE);
//	}
//	if (encounter == 250) {
//		syoukan(C_SIZE * 2);
//	}
//	if (encounter == 270) {
//		syoukan(C_SIZE * 3);
//	}
//	if (encounter == 290) {
//		syoukan(C_SIZE * 4);
//	}
//	if (encounter == 310) {
//		syoukan(C_SIZE * 5);
//	}
//	if (encounter == 330) {
//		syoukan(C_SIZE * 6);
//	}
//	if (encounter == 350) {
//		syoukan(C_SIZE * 5);
//	}
//	if (encounter == 370) {
//		syoukan(C_SIZE * 4);
//	}
//	if (encounter == 390) {
//		syoukan(C_SIZE * 3);
//	}
//	if (encounter == 410) {
//		syoukan(C_SIZE * 2);
//	}
//	if (encounter == 450 || encounter == 470 || encounter == 490) {
//		syoukan(C_SIZE * 4);
//	}
//	if (encounter == 530 || encounter == 550 || encounter == 570) {
//		syoukan(C_SIZE * 3);
//	}
//	if (encounter == 590 || encounter == 610 || encounter == 630) {
//		syoukan(C_SIZE * 5);
//	}
//	if (encounter == 700) {
//		syoukan(0);
//	}
//	if (encounter == 700) {
//		syoukan(WND_W - C_SIZE);
//	}
//	if (encounter == 720) {
//		syoukan(C_SIZE);
//	}
//	if (encounter == 720) {
//		syoukan(WND_W - C_SIZE * 2);
//	}
//	if (encounter == 740) {
//		syoukan(C_SIZE * 2);
//	}
//	if (encounter == 760) {
//		syoukan(C_SIZE * 3);
//	}
//	if (encounter == 780) {
//		syoukan(C_SIZE * 4);
//	}
//	if (encounter == 800) {
//		syoukan(C_SIZE * 5);
//	}
//	if (encounter == 820) {
//		syoukan(C_SIZE * 6);
//	}
//	if (encounter == 840) {
//		syoukan(C_SIZE * 7);
//	}
//	if (encounter == 740) {
//		syoukan(WND_W - C_SIZE * 3);
//	}
//	if (encounter == 760) {
//		syoukan(WND_W - C_SIZE * 4);
//	}
//	if (encounter == 780) {
//		syoukan(WND_W - C_SIZE * 5);
//	}
//	if (encounter == 800) {
//		syoukan(WND_W - C_SIZE * 6);
//	}
//	if (encounter == 820) {
//		syoukan(WND_W - C_SIZE * 7);
//	}
//	if (encounter == 840) {
//		syoukan(WND_W - C_SIZE * 8);
//	}
//}
//
//void CEnemy::Draw(CCamera* pCamera)
//{
//	
//	for (int i = 0; i < E_MAX; i++)
//	{
//		if (m_EnemyState[i] == enCharaState::Living)
//		{
//			m_FrameSplit.w = 64;
//			m_FrameSplit.h = 64;
//			m_FrameSplit.x = 0;
//			m_FrameSplit.y = 64*2;
//			VECTOR2 DispPos = pCamera->CalcToPositionInCamera(&m_EPosition[i], &m_FrameSplit);
//			//“G‚Ì•\Ž¦
//			m_pImg->TransBlt(
//				m_EPosition[i].x,
//				m_EPosition[i].y,
//				//vertical = rand() % (480 - 128),
//				m_FrameSplit.w,
//				m_FrameSplit.h,
//				m_FrameSplit.x,
//				m_FrameSplit.y);
//
//		}
//		else if (m_EnemyState[i] == enCharaState::Deading)
//		{
//			EEXP_IMG->TransBlt(
//				m_EPosition[i].x,
//				m_EPosition[i].y,
//				64,
//				64,
//		
//         		(m_EnemyExpAnimCnt[i] % 8) * 64,
//				(m_EnemyExpAnimCnt[i] / 8) * 64);
//		}
//		if (m_EnemyState[i] == enCharaState::Deading)
//		{
//			m_EnemyExpAnimCnt[i]++;
//			if (m_EnemyExpAnimCnt[i] >= 30)
//			{
//				m_EnemyState[i] = enCharaState::Dead;
//			}
//		
//		}
//
//
//
//
//
//	}
//	
//}
//void CEnemy::syoukan(int x)
//{
//	for (int i = 0; i < E_MAX; i++)//“G‹@‚Ì”‚¾‚¯ˆ—‚·‚é.
//	{
//		if (m_EnemyState[i] == enCharaState::Standby) {
//			m_EPosition[i].x = x;	//”CˆÓ‚ÌêŠ‚ÉoŒ»
//			m_EPosition[i].y = -C_SIZE;
//			m_EnemyState[i] = enCharaState::Living;	//Ž€–S’†
//			m_EnemyExpAnimCnt[i] = 0;
//			break;
//		}
//	}
//
//}
//
//void CEnemy::HIT(int i)
//{
//	
//		m_EnemyState[i] = enCharaState::Deading;
//		m_Killcnt += 1;
//	CSoundManager::PlaySE(CSoundManager::enList::SE_Ken);
//
//
//}
