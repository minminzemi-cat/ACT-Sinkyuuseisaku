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
	int  hozonnyou = score;
	//計算
	int keisann = score;

	while (hozonnyou != 0)
	{
		hozonnyou = hozonnyou / 10;
		keta++;

	}
	if (keta == 0) {

		m_ScoreImg->TransBlt(
			200, // X座標
			200,     // Y座標
			65, 85, //画像幅、高さ.
			0, 0); //元画像x,y座標.
	}
	else {
		int t;
		for (int i = 0; i < keta; i++) {
			m_ScoreImg->TransBlt(
				200 - 20 * i, // X座標
				200,     // Y座標
				65, 85, //画像幅、高さ.
				65 * (keisann % 10), 0); //元画像x,y座標.
			keisann /= 10;
		}
	}

}
