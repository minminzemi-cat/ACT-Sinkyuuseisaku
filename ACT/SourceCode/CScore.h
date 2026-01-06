#pragma once
#include<Windows.h>
#include"Global.h"
#include"CImage.h"
#include "CCamera.h"	//カメラクラス.
#include "MyMath.h"	//カメラクラス.


/***********************************
***		スコアクラス
***************************/

class CScore
{
public:
	
	//-------------定数宣言---------------
	static const int SCORE_MAX = 10;		//スコアの桁数

public:
	CScore();
	~CScore();

public:
	void Update();
	//画像読み込み
	void SetImageScore(CImage* pImg, int score) { m_ScoreImg = pImg; }

	void Draw(CCamera* pCamera, int score);

	//このクラスで描画の処理入れたいから引数にメモリDCが必要
	void TitleDraw(CCamera* pCamera,int score);


	char m_scoreStr[20] = "";

	//ここにはスコア
	int m_Score;

	//ハイスコア
	int m_HightScore;

	CImage* m_ScoreImg;
};
