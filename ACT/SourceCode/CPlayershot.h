#pragma once
#include "AllShot.h"
#include "CPlayer.h"

#include "CSoundManager.h"	//サウンドマネージャクラス.
class PSHOT
	: public AllShot	//キャラクタークラスを継承.
{
public:
	PSHOT();
	~PSHOT();

	//動作関数.
	void UpdateShot() override;	//override:再定義前の関数が仮想関数かチェックできる.
	//---------------------						//		   仮想関数でない場合はエラーになる.
	//描画関数.
	//------------------------
	void DrawShot(CCamera* pCamera) override;

	void DrawBomShot(CCamera* pCamera);

	void DrawBomset(CCamera* pCamera);

	void DrawSpecialmove(CCamera* pCamera);

	

	//プレイヤーのショット画像
	void SetImagePshot(CImage* sh) { PShotImg = sh; }
	//プレイヤーのボムショット画像
	void SetImageBshot(CImage* sh) { BShotImg = sh; }
	//プレイヤーのボムショット画像
	void SetImageBomset(CImage* sh) { BomsetImg = sh; }
	//プレイヤーの必殺画像
	void SetImageSP(CImage* sh) { SPImg = sh; }
	

	VECTOR2 GetPsPosition() { return m_PsPosition[PS_MAX]; }


	void SetPlayer(CPlayer* sh) { player = sh; }

	VECTOR2 SetPos(CPlayer* sh) { playerpos = sh; }

private:

	CPlayer* playerpos;
	CPlayer* player;
	
	CImage* PShotImg;
	CImage* BShotImg;
	CImage* BomsetImg;
	CImage* SPImg;


	bool    m_ShotFlag[PS_MAX];		//弾打ったかどうか
	bool    m_BomShotFlag[BS_MAX];	//ボム打ったかどうか
	int     m_BomRostCnt[BS_MAX];	//ボムが消滅するまで
	int S;
	/*int SP;*/
	int i;
	bool    m_xHanFlag[BS_MAX];		//ボムの反射ｘ
	bool    m_yHanFlag[BS_MAX];		//ボムの反射ｙ
	//bool    m_Special;			    //必殺居合切り
	//bool    m_Specialmove;			//必殺居合切り
	bool    SPGEAG;

};

