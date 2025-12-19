#pragma once
#include "MyMath.h"			//数学クラス.
#include "CImage.h"
#include "CCamera.h"	//カメラクラス.

class CEnding
{
public:
	CEnding();
	~CEnding();

	void Update();

	void Draw(CCamera* pCamera);


	void SetImageEnding(CImage* tit) {
		EndingIMG = tit;
	};

private:
	CImage* EndingIMG;
	float  m_back_y;
};

