#include"CTitle.h"

CTitle::CTitle()
	:m_pSentakuImg(nullptr)
{
}

CTitle::~CTitle()
{

}




//描画関数
void CTitle::Draw(CCamera* pCamera)
{


	//ゲームスタート
	m_pSentakuImg->TransBlt(
		140,					//表示位置x座標
		300,					//表示位置y座標.
		200,				//画像幅
		70,					//画像高さ.
		0,					//元画像x座標.・・・座標0,0から画像幅、高さ分を取り出しますよ
		0);					//元画像y座標.

	//音量設定
	m_pSentakuImg->TransBlt(
		140,					//表示位置x座標
		400,					//表示位置y座標.
		200,				//画像幅
		70,					//画像高さ.
		0,					//元画像x座標.・・・座標0,0から画像幅、高さ分を取り出しますよ
		70);					//元画像y座標.

	//ゲーム終了
	m_pSentakuImg->TransBlt(
		140,					//表示位置x座標
		520,					//表示位置y座標.
		200,				//画像幅
		70,					//画像高さ.
		0,					//元画像x座標.・・・座標0,0から画像幅、高さ分を取り出しますよ
		170);					//元画像y座標.

}

//動作関数
void CTitle::Update()
{

	
	
	

}



