#pragma once
#include"CImage.h"
#include"Global.h"
#include"CCamera.h"

class CTitle
{
public:


public:

	CTitle();
	~CTitle();

public:

	//画像を読み込ませるための関数
	void SetImageBoss(CImage* pImg) { m_pSentakuImg = pImg; }
	//このクラスで描画の処理入れたいから引数にメモリDCが必要
	void Draw(CCamera* pCamera);
	void Update();

public:

private:
	CImage* m_pSentakuImg;
	



};
