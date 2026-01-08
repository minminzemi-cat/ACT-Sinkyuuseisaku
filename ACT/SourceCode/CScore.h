#pragma once
#include<Windows.h>
#include"Global.h"
#include"CImage.h"
#include "CCamera.h"	//カメラクラス.
#include "MyMath.h"	


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
	void SetImageScore(CImage* pImg) { m_ScoreImg = pImg; }
	void SetImagMini(CImage* pImg) { m_miniScoreImg = pImg; }


	//このクラスで描画の処理入れたいから引数にメモリDCが必要
	void TitleDraw(CCamera* pCamera,int score);

	//ゲームメインに表示する
	void MainDraw( int x, int y,int score);


	//リザルト画面に表示するハイスコア
	void ResultHiDraw(int x, int y, int score);

	//リザルト画面に表示するスコア
	void ResultDraw(int x, int y, int score);

	char m_scoreStr[20] = "";



	//このスコアはプレイして出てきたスコアを入れる
	int m_Score;

	//ハイスコア
	int m_HightScore=0;

	CImage* m_ScoreImg;
	CImage* m_miniScoreImg;

};