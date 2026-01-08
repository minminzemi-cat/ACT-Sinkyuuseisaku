#include "CGameClear.h"


//コンストラクタ
CGameClear::CGameClear()
{
}

//デストラクタ
CGameClear::~CGameClear()
{
}

//描画
void CGameClear::Draw(CCamera* pCamera)
{
	m_FrameSplit.w = 480;
	m_FrameSplit.h = 640;
	m_FrameSplit.x = 0;
	m_FrameSplit.y = 0;

	m_Position.x = 0;
	m_Position.y = 0;


	m_ClearImg->TransBlt(
		m_Position.x,
		m_Position.y,					//表示位置x,y座標.
		m_FrameSplit.w,
		m_FrameSplit.h,					//画像幅、高さ.
		m_FrameSplit.x,
		m_FrameSplit.y);				//元画像x,y座標.
}