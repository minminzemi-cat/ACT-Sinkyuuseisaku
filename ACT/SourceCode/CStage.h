#pragma once
#include "CGameObject.h"//ゲームオブジェクトクラス.
#include "CImage.h"
#include<Windows.h>
#include "Global.h"		//ウィンドウサイズで必要.
#include "MyMath.h"		//VECTOR2構造体で必要.


/**************************************************
*   ステージクラス.
**/
class CStage
	: public CGameObject	//ゲームオブジェクトクラスを継承.
{
public:
	static const int DATA_X_MAX = 20;
	static const int DATA_Y_MAX = 15;

public:
	CStage();
	~CStage();

	void Update() override;
	void Draw( CCamera* pCamera ) override;
	void SCOAR(int x, int y);


	void SetImage( CImage* pImg ) { m_pImg = pImg; }

	void SetImageBack(CImage*bg) { m_pBackImg = bg; }

	void SetImageScore(CImage* bg) { m_pscoreImg = bg; }


	//ステージの幅を取得.※データ読込完了後のみ取得可能.
	int GetWidth() const { return m_Chip.w * m_MapMax.x; }
	int m_Score;


private:
	CImage*	m_pImg;
	CImage* m_pBackImg;
	CImage* m_pscoreImg;
	CImage::FRAMESPLIT	m_Chip;	//マップチップ画像１つあたりの幅高さ.
	CImage::FRAMESPLIT	m_FrameSplit;	//１コマの画像情報.
	HDC     m_hMemDC;  //メモリデバイスコンテキスト.
	int			m_Data[DATA_Y_MAX][DATA_X_MAX];		//マップデータ.
	GameWindow* m_pGameWnd;
	VECTOR2		m_MapMax;	//マップデータの縦と横の最大数.
	int**		m_ppData;	//マップデータ(ポインタのポインタorダブルポインタ).
	int  m_back_y;
	VECTOR2		m_Position;		//ステージ位置.
};