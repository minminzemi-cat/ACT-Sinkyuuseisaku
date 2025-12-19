#pragma once
#include "AllShot.h"
#include "CPlayer.h"
#include "CEnemy.h"
#include "CSoundManager.h"	//サウンドマネージャクラス.
class Exculibur
	: public  AllShot//キャラクタークラスを継承.

{
public:
	Exculibur();
	~Exculibur();

   void UpdateKen();
   void DrawShotKen(CCamera* pCamera);
   void DrawGeag(CCamera* pCamera);
   void SPHIT();
   void SetImageKen(CImage* sh) { KENIMG = sh;}
 
   VECTOR2 GetKenPosition() { return m_KenPosition; }
   VECTOR2 GetSPsPosition() { return  m_SPsPosition; }
   bool     GetEXUse() { return EX; }


   bool GetIAI() { return m_Specialmove; }

   void SetPlayer(CPlayer* sh) { player = sh; }
   //プレイヤーの必殺画像
   void SetImageSP2(CImage* sh) { SP2Img = sh; }
   //プレイヤーの必殺ゲージ
   void SetImageGeag(CImage* sh) { SPGeagImg = sh; }


   void SetEne(CEnemy* tit) {m_enemy = tit;}

private:
	int D;
	int M;
	int SP;
	
	CPlayer* player;
	CEnemy* m_enemy;
	CImage* KENIMG;
	CImage* SPGeagImg;
	CImage* SP2Img;
	bool    m_Special;			    //必殺居合切り
	bool    m_Specialmove;			//必殺居合切り
	bool	Ken;
	bool EX;
	
};

