#pragma once
#include"CImage.h"
#include"Global.h"
#include"CCamera.h"
#include "MyMath.h"	//カメラクラス.

class CTitle
{
public:


public:

	CTitle();
	~CTitle();

public:

	//画像を読み込ませるための関数
	void SetImageTitle(CImage* pImg) { m_pSentakuImg = pImg; }

	//タイトル背景の読み込み
	void SetImageBack(CImage* pImg) { m_pTitleBackImg = pImg; }

	//タイトル選択の剣
	void SetImageSord(CImage* pImg) { m_pKennImg = pImg; }

	//選択肢の描画
	void Draw(CCamera* pCamera);

	//背景の表示
	void XDraw(CCamera* pCamera);

	//剣の表示
	void RDraw(CCamera* pCamera);


	void Update();



public:

private:
	CImage* m_pSentakuImg;
	CImage* m_pTitleBackImg;
	CImage* m_pKennImg;

	int m_TitleSword;

};
