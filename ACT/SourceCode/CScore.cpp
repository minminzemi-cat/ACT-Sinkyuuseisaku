#include "CScore.h"

CScore::CScore()
	
{
}

CScore::~CScore()
{
}

void CScore::Update()
{
}



//このクラスで描画の処理入れたいから引数にメモリDCが必要
void CScore::TitleDraw(CCamera* pCamera, int score)
{

	//谷口君から教えてもらったスコアの処理

	//桁
	int keta = 0;
	
	//今プレイしたスコアがハイスコアより大きいとき
	if (score >= m_HightScore)
	{
		//ハイスコアに今のスコアを代入
		m_HightScore = score;
		
	}

	//今プレイして得たスコアがハイスコアより小さいとき
	if (score <= m_HightScore)
	{
		//何もしない
	}


	//ここにハイスコアが入ります
	m_HightScore = score;
	//計算
	int keisann = score;

	while(m_HightScore != 0)
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
				300 - 64 * i,			//X座標
				220,					//Y座標
				64, 64,					//画像幅、高さ.
				63 * (keisann % 10), 0); //元画像x,y座標.
			keisann /= 10;
		}
	}

}
