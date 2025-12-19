#include "Ending.h"

CEnding::CEnding()
{
}

CEnding::~CEnding()
{
}

void CEnding::Update()
{
	if (m_back_y > -WND_H)
	{
		if (m_back_y < 640)
		{
			m_back_y += 0.5;
	    }
	}
	else
	{
		m_back_y = WND_H;
	}
}

void CEnding::Draw(CCamera* pCamera)
{
	//EndingIMG->TransBlt(0, 0, 480, 640, 0, 0);

	//ステージの表示座標を算出
	{

		EndingIMG->BBlt(

			0, 0,
			WND_W, WND_H,
			0, m_back_y);
		if (m_back_y < 0) {
			//背景の表示
			EndingIMG->BBlt(
				0, 0,
				WND_W, -(m_back_y),
				0,
				(WND_H * 2 + m_back_y));
		}

	}
}