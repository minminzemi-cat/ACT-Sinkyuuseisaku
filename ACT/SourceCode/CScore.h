//#pragma once
//#include<Windows.h>
//#include"Global.h"
//#include"CImage.h"
//
//
//
///***********************************
//***		スコアクラス
//***************************/
//
//class CScore
//{
//public:
//	
//	//-------------定数宣言---------------
//	static const int SCORE_MAX = 10;		//スコアの桁数
//
//public:
//	CScore();
//	~CScore();
//
//public:
//	void Update();
//
//	//画像を読み込ませるための関数
//	void Init(HDC hScreenDC, HDC hMemDC, HDC hWorkDC);
//
//	void Draw(HDC pgame, int score);
//
//	//このクラスで描画の処理入れたいから引数にメモリDCが必要
//	void TitleDraw(HDC m_hMemDC, int score);
//
//
//	char m_scoreStr[20] = "";
//
//	//ここにはスコア
//	int m_Score;
//
//	//ハイスコア
//	int m_HightScore;
//
//	CImage* m_pScoreImg;
//};
