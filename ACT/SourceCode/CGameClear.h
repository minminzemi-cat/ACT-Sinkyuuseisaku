#pragma once
#include"CImage.h"
#include"Global.h"
#include"CCamera.h"
#include "MyMath.h"	//ƒJƒƒ‰ƒNƒ‰ƒX.

class CGameClear
{
public:
	CGameClear();
	~CGameClear();

public:

	void SetImagClear(CImage* pImg) { m_ClearImg = pImg; }

	void Draw(CCamera* pCamera);

public:

	CImage* m_ClearImg;

	CImage::FRAMESPLIT m_FrameSplit;
	VECTOR2 m_Position;

};
