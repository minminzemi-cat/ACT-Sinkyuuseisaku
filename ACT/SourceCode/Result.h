#pragma once
#include "MyMath.h"			//数学クラス.
#include "CImage.h"
#include "CCamera.h"	//カメラクラス.
#include "CEnemy.h"	//カメラクラス.
#include "Excalibur.h"
#include "CCharacter.h"

class CResult
	:CCharacter
{
	enum enRank
	{
		SOLDIER,
		KNIGHT ,
		HERO   ,
		LEGEND ,
		ZOMBIE ,
		Shooter,
		SWORDSA,
		SLAYER ,
		MG_PEAC,
	};
public:
	CResult();
	~CResult();

	void Update();

	void Draw(CCamera* pCamera);


	void SetImageResult(CImage* tit) {
		ResultIMG = tit;
	};

	void SetImageRank(CImage* tit) {
		RankIMG = tit;
	};

	void SetEn(CEnemy* tit) {
		m_enemy = tit;
	};

	void SetEx(Exculibur* tit) {
		exc = tit;
	};


private:
	CImage* ResultIMG;
	CImage* RankIMG;
	CEnemy* m_enemy;
	Exculibur* exc;
	//CCharacter* CH;
	int     m_Rank;

};

