#include"CTitle.h"

CTitle::CTitle()
		: m_TitleSword(300)
{
}

CTitle::~CTitle()
{

}






//剣の描画
void CTitle::RDraw(CCamera* pCamera)
{

	m_pKennImg->TransBlt(
		30,					//表示位置x座標
		m_TitleSword,					//表示位置y座標.
		100,				//画像幅
		100,					//画像高さ.
		0,					//元画像x座標.・・・座標0,0から画像幅、高さ分を取り出しますよ
		0);					//元画像y座標.

}


//背景の描画
void CTitle::XDraw(CCamera* pCamera)
{
	m_FrameSplit.w = 480;
	m_FrameSplit.h = 640;
	m_FrameSplit.x = 0;
	m_FrameSplit.y = 0;

	m_Position.x = 0;
	m_Position.y = 0;


	m_pTitleBackImg->TransBlt(
		m_Position.x,
		m_Position.y,							//表示位置x,y座標.
		m_FrameSplit.w, 
		m_FrameSplit.h,					//画像幅、高さ.
		m_FrameSplit.x,
		m_FrameSplit.y);						//元画像x,y座標.
		

}


//動作関数
void CTitle::Update()
{
	

	if (GetAsyncKeyState(VK_UP) & 0x0001)//アップキー
	{
		//剣が画面買いに行かないようにする処理
		if (m_TitleSword >= 300) {
			//剣の画像がアップキーを押された場合どのような動きをするか
			m_TitleSword -= 120;
		}

	}


	if (GetAsyncKeyState(VK_DOWN) & 0x0001)//ダウンキー
	{
		//剣が画面外にいかないようにする処理
		if (m_TitleSword < 420) {

			m_TitleSword += 120;

		}

	}

}



