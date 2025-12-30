#pragma once
#include"CImage.h"
#include"Global.h"


class CTitle
{
public:


public:

	CTitle();
	~CTitle();

public:

	//画像を読み込ませるための関数
	void Init(HDC hScreenDC, HDC hMemDC, HDC hWorkDC);
	//このクラスで描画の処理入れたいから引数にメモリDCが必要
	void Draw(HDC m_hMemDC);				
	void Update();

public:

private:
	CImage* m_pSentakuImg;
	



};
