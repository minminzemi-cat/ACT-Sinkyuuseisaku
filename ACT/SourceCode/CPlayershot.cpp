#include "CPlayershot.h"

PSHOT::PSHOT()
	:PShotImg(nullptr)

{
	m_ShotFlag[BS_MAX] = false;
	m_BomShotFlag[BS_MAX] = false;
	m_xHanFlag[BS_MAX] = false;
	m_yHanFlag[BS_MAX] = false;
	m_BomRostCnt[BS_MAX] = false;
	//m_Special = false;
	//m_Specialmove = false;
	m_SpAnimCnt = 0;
	m_BsPosition[1].x -= 1000;
	m_BsPosition[1].y -= 1000;
	m_BsPos.x=-1000;
	m_BsPos.y=-1000;
	SPGEAG = 0;
	S = 0;
}

PSHOT::~PSHOT()
{
}

void PSHOT::UpdateShot()
{


//-----------------------------------
//プレイヤー通常ショット
//-----------------------------------
	if (GetAsyncKeyState('Z') & 0x8000)
	{
		for (int pNo = 0; pNo < PS_MAX; pNo++)
		{
			if (m_ShotFlag[pNo] == false)
			{
				m_PsPosition[pNo] = player->GetPosition();
				m_ShotFlag[pNo] = true;
				break;
			}

		}
	}
	for (int pNo = 0; pNo < PS_MAX; pNo++) 
	{
		if (m_ShotFlag[pNo] == true)
		{

			m_PsPosition[pNo].y -= 10;
			if (m_PsPosition[pNo].y <= 0)
			{
				m_ShotFlag[pNo] = false;
			}
		}
	}
//-----------------------------------
//プレイヤーボムショット
//-----------------------------------

	if (GetAsyncKeyState('X') & 0x8000)
	{
		for (int b = 0; b < BS_MAX; b++)
		{
			if (m_BomShotFlag[b] == false)
			{
				m_BsPosition[b] = player->GetPosition();
				CSoundManager::PlaySE(CSoundManager::enList::SE_Shot2);
				m_BomShotFlag[b] = true;
				i -= 1;
				break;
			}
		}
	}

	for (int b = 0; b < BS_MAX; b++)
	{
		if (m_BomShotFlag[b] == true)
		{
			if (m_xHanFlag[b] == true){
				m_BsPosition[b].x += 5;
			}else if(m_xHanFlag[b] == false){
				m_BsPosition[b].x -= 5;
			}

			if (m_yHanFlag[b] == true){
				m_BsPosition[b].y += 5;
			}else if (m_yHanFlag[b] == false){
				m_BsPosition[b].y -= 5;
			}

			//反射してるか否か
			if (m_BsPosition[b].x < 0)
			{
				CSoundManager::PlaySE(CSoundManager::enList::SE_Han);
				m_xHanFlag[b] = true;
				m_BomRostCnt[b] += 1;
			}
			else if (m_BsPosition[b].x > 480-64)
			{
				CSoundManager::PlaySE(CSoundManager::enList::SE_Han);
				m_xHanFlag[b] = false;
				m_BomRostCnt[b] += 1;
			}

			if (m_BsPosition[b].y < 0)
			{
				CSoundManager::PlaySE(CSoundManager::enList::SE_Han);
				m_yHanFlag[b] = true;
				m_BomRostCnt[b] += 1;
			}
			else if (m_BsPosition[b].y > 640-64)
			{
				CSoundManager::PlaySE(CSoundManager::enList::SE_Han);
				m_yHanFlag[b] = false;
				m_BomRostCnt[b] += 1;
			}
		}
	}


}
//-----------------------------------
//プレイヤーショット
//-----------------------------------
void PSHOT::DrawShot(CCamera* pCamera)
{
	for (int pNo = 0; pNo < PS_MAX;pNo++) 
	{
		if (m_ShotFlag[pNo] == true)
		{
			m_FrameSplit.w = 64;
			m_FrameSplit.h = 64;
			m_FrameSplit.x = 64;
			m_FrameSplit.y = 0;

			VECTOR2 DispPos = pCamera->CalcToPositionInCamera(&m_PsPosition[pNo], &m_FrameSplit);

			//敵の表示.
			PShotImg->TransAlBlend(
				DispPos.x,      //表示位置x座標.
				DispPos.y,      //表示位置y座標.
				m_FrameSplit.w, //表示幅.
				m_FrameSplit.h, //表示高さ.
				m_FrameSplit.x, //元画像読込開始x座標.
				m_FrameSplit.y, //元画像読込開始y座標.
				127);          //α値.
		}
	}
}
//-----------------------------------
//プレイヤーボムショット
//-----------------------------------
void PSHOT::DrawBomShot(CCamera* pCamera){
	for (int b = 0; b <=1; b++) {
		if (m_BomShotFlag[b] == true && m_BomRostCnt[b] <= 10){
			S += 15;
			m_FrameSplit.w = 64;
			m_FrameSplit.h = 64;
			m_FrameSplit.x = 64 * 2;
			m_FrameSplit.y = 0;

			    m_BsPos.x= m_BsPosition[b].x;
				m_BsPos.y= m_BsPosition[b].y;
			VECTOR2 DispPos = pCamera->CalcToPositionInCamera(&m_BsPos, &m_FrameSplit);

			//敵の表示.
			BShotImg->TransSpinAlBlt(
				DispPos.x,      //表示位置x座標.
				DispPos.y,      //表示位置y座標.
				m_FrameSplit.w, //表示幅.
				m_FrameSplit.h, //表示高さ.
				m_FrameSplit.x, //元画像読込開始x座標.
				m_FrameSplit.y, //元画像読込開始y座標.
				64, 64,
				S, 200);          //α値.

			if (m_BomRostCnt[b] >= 10) {
				m_BomShotFlag[b] = false;
				m_BomRostCnt[b] = 0;
			}
		}
	}
}
void PSHOT::DrawBomset(CCamera* pCamera)
{
	for (int b = 0; b < 2; b++)
	{

		m_FrameSplit.w = 64 * i;
		m_FrameSplit.h = 64;
		m_FrameSplit.x = 64 * i;
		m_FrameSplit.y = 0;

		VECTOR2 DispPos = pCamera->CalcToPositionInCamera(&m_bomsetPosition, &m_FrameSplit);

		//敵の表示.
		BomsetImg->TransAlBlend(
			DispPos.x,      //表示位置x座標.
			DispPos.y,      //表示位置y座標.
			m_FrameSplit.w, //表示幅.
			m_FrameSplit.h, //表示高さ.
			m_FrameSplit.x, //元画像読込開始x座標.
			m_FrameSplit.y, //元画像読込開始y座標.
			127);          //α値.
	}
}





//-----------------------------------
//プレイヤー居合切り（必殺技）
//-----------------------------------
void PSHOT::DrawSpecialmove(CCamera* pCamera)
{
	//for (int eNo = 0; eNo <= 1; eNo++)
	//{
	//	if (m_Specialmove == true)
	//	{
	//		m_FrameSplit.w = 64;
	//		m_FrameSplit.h = 100;
	//		m_FrameSplit.x = 64 * 3;
	//		m_FrameSplit.y = 64;

	//		VECTOR2 DispPos = pCamera->CalcToPositionInCamera(&m_SPsPosition, &m_FrameSplit);

	//		//敵の表示.
	//		SPImg->TransAlBlend(
	//			DispPos.x,      //表示位置x座標.
	//			DispPos.y,      //表示位置y座標.
	//			m_FrameSplit.w, //表示幅.
	//			m_FrameSplit.h, //表示高さ.
	//			m_FrameSplit.x, //元画像読込開始x座標.
	//			m_FrameSplit.y, //元画像読込開始y座標.
	//			127);          //α値.
	//	}
	//	if (m_Special == true)
	//	{
	//		SP2Img->TransBlt(
	//			m_SPsPosition.x,
	//			m_SPsPosition.y,
	//			300,
	//			200,
	//			(m_SpAnimCnt % 7) * 300,
	//			0);
	//	}

	//	if (m_Special == true)
	//	{
	//		m_SpAnimCnt++;
	//		if (m_SpAnimCnt >= 7)
	//		{
	//			m_Special = false;
	//			m_SpAnimCnt = 0;
	//		}
	//		break;
	//	}
	//}
	
}
//-----------------------------------
//プレイヤーゲージ（必殺技）
//-----------------------------------
//void PSHOT::DrawGeag(CCamera* pCamera)
//{
//	
//			m_FrameSplit.w = 300;
//			m_FrameSplit.h = 30;
//			m_FrameSplit.x = 0;
//			m_FrameSplit.y = 30*SP;
//		
//	
//
//
//	VECTOR2 DispPos = pCamera->CalcToPositionInCamera(&m_GeagPosition, &m_FrameSplit);
//
//	//敵の表示.
//	SPGeagImg->TransAlBlend(
//		DispPos.x,      //表示位置x座標.
//		DispPos.y,      //表示位置y座標.
//		m_FrameSplit.w, //表示幅.
//		m_FrameSplit.h, //表示高さ.
//		m_FrameSplit.x, //元画像読込開始x座標.
//		m_FrameSplit.y, //元画像読込開始y座標.
//		127);          //α値.
//}


