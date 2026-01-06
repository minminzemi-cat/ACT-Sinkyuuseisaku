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



	//タイトル背景の読み込み
	void SetImageBack(CImage* pImg) { m_pTitleBackImg = pImg; }

	//タイトル選択の剣
	void SetImageSord(CImage* pImg) { m_pKennImg = pImg; }


    // m_TitleSword のアクセス修飾子を public に変更
    public:
					int m_TitleSword;
	//背景の表示
	void XDraw(CCamera* pCamera);

	//剣の表示
	void RDraw(CCamera* pCamera);


	void Update();



public:

private:
	CImage* m_pTitleBackImg;
	CImage* m_pKennImg;

	VECTOR2 m_Position;
	CImage::FRAMESPLIT m_FrameSplit;
};
