#include "CScore.h"

CScore::CScore()
	:m_ScoreImg(nullptr)
{
}

CScore::~CScore()
{
}

void CScore::Update()
{
}



void CScore::Draw(CCamera* pCamera,int score)
{
	
	//wsprintf(m_scoreStr, //これを表示させる
	//	"score[%03d]", 
	//	(DWORD)score);

	////スコアの表示.
	//TextOut(pCamera,
	//	0,					//X座標
	//	0,						//Y座標
	//	m_scoreStr,				//文字列
	//	lstrlen(m_scoreStr));		//文字はこのくらいありますよ


		
}


//このクラスで描画の処理入れたいから引数にメモリDCが必要
void CScore::TitleDraw(CCamera* pCamera, int score)
{

	//谷口君から教えてもらったスコアの処理

	//桁
	int keta = 0;
	//ここにスコアが入ります
	m_HightScore = score;
	//計算
	int keisann = score;

	while (m_HightScore != 0)
	{
		m_HightScore = m_HightScore / 10;
		keta++;

	}
	if (keta == 0) {

		//この４つの描画処理は０を４つ表示させる
		m_ScoreImg->TransBlt(
			108,		//表示させるX座標
			220,		//表示させるY座標
			64,			//画像幅
			64,			//画像高さ.	
			3,			//元画像x
			0);			//元画像y座標.

		m_ScoreImg->TransBlt(
			172,		//表示させるX座標
			220,		//表示させるY座標
			64,			//画像幅
			64,			//画像高さ.	
			3,			//元画像x
			0);			//元画像y座標.

		m_ScoreImg->TransBlt(
			236,		//表示させるX座標
			220,		//表示させるY座標
			64,			//画像幅
			64,			//画像高さ.	
			3,			//元画像x
			0);			//元画像y座標.

		m_ScoreImg->TransBlt(
			300,		//表示させるX座標
			220,		//表示させるY座標
			64,			//画像幅
			64,			//画像高さ.	
			3,			//元画像x
			0);			//元画像y座標.
						
	}
	else {
		for (int i = 0; i < keta; i++) {
			m_ScoreImg->TransBlt(
				200 - 20 * i,			//X座標
				108,					//Y座標
				64, 64,					//画像幅、高さ.
				64 * (keisann % 10), 0); //元画像x,y座標.
			keisann /= 10;
		}
	}

}
