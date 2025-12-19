#include "Excalibur.h"
#include <math.h>

Exculibur::Exculibur()
{
	D = 0;
	M = 0;
	EX  =  false;
	Ken =  false;
	m_Special     = false;
	m_Specialmove = false;
	m_KenPosition.x = 1000;
	m_KenPosition.y = 1000;
}

Exculibur::~Exculibur()
{
}

void Exculibur::UpdateKen()
{

//-----------------------------------
//お試しげーじあっぷ
//-----------------------------------
	if (GetAsyncKeyState('C') & 0x8000 && SP <= 9)
	{
		if (SP >= 9)
		{
			CSoundManager::PlaySE(CSoundManager::enList::SE_GMAX);
		}
		SP++;
	}

	if (GetAsyncKeyState(VK_SHIFT) & 0x8000 
		&&Ken == false) {
		Ken = true;
		EX  = true;
		CSoundManager::PlaySE(CSoundManager::enList::SE_KenMove);
	}

//-----------------------------------
//　　　カウンター居合切り
//-----------------------------------
	if (GetAsyncKeyState('A') & 0x8000);
	{
		for (int s = 0; s < 1; s++)
		{
			if (m_Specialmove == false && SP==9)
			{
				m_Specialmove = true;
				EX =true;
				CSoundManager::PlaySE(CSoundManager::enList::SE_IAI);
				m_SPsPosition = player->GetPosition();
			}
		}
	}

	
	if (m_Specialmove == true && GetAsyncKeyState(VK_SHIFT) & 0x8000)
	{
		CSoundManager::Stop(CSoundManager::enList::SE_IAI);
		m_Special = true;
		m_Specialmove = false;
		CSoundManager::PlaySE(CSoundManager::enList::SE_SP);
	}
}
//-----------------------------------
//　　　カウンター居合切り2
//-----------------------------------
void Exculibur::SPHIT()
{
	if (m_Specialmove == true)
	{
		CSoundManager::Stop(CSoundManager::enList::SE_IAI);
		m_Special = true;
		m_Specialmove = false;
		CSoundManager::PlaySE(CSoundManager::enList::SE_SP);
	}
}



void Exculibur::DrawShotKen(CCamera* pCamera)
{
	if (Ken == true&&D<=180) {
		D += 8;
		VECTOR2 PS = { player->GetPosition() };
		PS.x += 64 / 2;
		PS.y += 64 / 2;

		VECTOR2 KS;

		double a = M_PI / 180;

		KS.y = PS.y + sin(-D * a) * (64 / 2 + 100 / 2);
		KS.x = PS.x + cos(-D * a) * (64 / 2 + 100 / 2);

		m_KenPosition.y = KS.y - 100 / 2;
		m_KenPosition.x = KS.x - 100 / 2;

		m_FrameSplit.w = 100;
		m_FrameSplit.h = 100;
		m_FrameSplit.x = 0;
		m_FrameSplit.y = 0;

		VECTOR2 DispPos = pCamera->CalcToPositionInCamera(&m_KenPosition, &m_FrameSplit);

		//敵の表示.
		KENIMG->TransSpinAlBlt(
			DispPos.x,      //表示位置x座標.
			DispPos.y,      //表示位置y座標.
			m_FrameSplit.w, //表示幅.
			m_FrameSplit.h, //表示高さ.
			m_FrameSplit.x, //元画像読込開始x座標.
			m_FrameSplit.y, //元画像読込開始y座標.
			100,
			100,
			-D, 200);          //α値.
		if (Ken == true && D >= 180)
		{
			Ken = false;
			D = 0;
		}
	}


	else if (m_Specialmove == true)
	{
		m_FrameSplit.w = 100;
		m_FrameSplit.h = 100;
		m_FrameSplit.x = 0;
		m_FrameSplit.y = 0;
		M = 230;
		m_KenPosition = player->GetPosition();
		VECTOR2 DispPos = pCamera->CalcToPositionInCamera(&m_KenPosition, &m_FrameSplit);

		//敵の表示.
		KENIMG->TransSpinAlBlt(
			DispPos.x,      //表示位置x座標.
			DispPos.y,      //表示位置y座標.
			m_FrameSplit.w, //表示幅.
			m_FrameSplit.h, //表示高さ.
			m_FrameSplit.x, //元画像読込開始x座標.
			m_FrameSplit.y, //元画像読込開始y座標.
			100,
			100,
			-M, 200);          //α値.
	}

//-----------------------------------
//　　　カウンター居合切り抜刀
//-----------------------------------
	for (int eNo = 0; eNo <= 1; eNo++)
	{
		if (m_Special == true)
		{

			VECTOR2 DispPos = pCamera->CalcToPositionInCamera(&m_SPsPosition, &m_FrameSplit);
			m_SPsPosition = player->GetPosition();
			SP2Img->TransBlt(
				0,
				0,
				480,
				640,
				(m_SpAnimCnt % 8) * 480,
				(m_SpAnimCnt / 8) * 480);
		}

		if (m_Special == true)
		{
			m_SpAnimCnt++;
			if (m_SpAnimCnt >= 16)
			{
				m_Special = false;
				m_SpAnimCnt = 0;
				SP = 0;
			}
			break;
		}
	}
}
//-----------------------------------
//プレイヤーゲージ（必殺技）
//-----------------------------------
void Exculibur::DrawGeag(CCamera* pCamera)
{

	m_FrameSplit.w = 300;
	m_FrameSplit.h = 30;
	m_FrameSplit.x = 0;
	m_FrameSplit.y = 30 * SP;




	VECTOR2 DispPos = pCamera->CalcToPositionInCamera(&m_GeagPosition, &m_FrameSplit);

	//敵の表示.
	SPGeagImg->TransAlBlend(
		DispPos.x,      //表示位置x座標.
		DispPos.y,      //表示位置y座標.
		m_FrameSplit.w, //表示幅.
		m_FrameSplit.h, //表示高さ.
		m_FrameSplit.x, //元画像読込開始x座標.
		m_FrameSplit.y, //元画像読込開始y座標.
		127);          //α値.
}


