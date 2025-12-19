#pragma once
#include "MyMath.h"			//数学クラス.
#include "CImage.h"
#include "CCamera.h"	//カメラクラス.

class CGameOver
{
public:
	CGameOver();
	~CGameOver();

	void Update();

	void Draw(CCamera* pCamera);


	void SetImageGameOver(CImage* tit) {
		GameOverIMG = tit;
	};

private:
	CImage* GameOverIMG;
};

