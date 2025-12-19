#pragma once
#include "CCharacter.h"		//キャラクタークラス.
#include "CCamera.h"		//カメラクラス.


/**************************************************
*   プレイヤークラス.
**/
class CPlayer
	: public CCharacter	//キャラクタークラスを継承.
{
public:
	//動作状態列挙型.
	enum enAction
	{
		Wait = 0,		//待機.
		MoveLeft,		//左移動.
		MoveRight,		//右移動.
		MoveUP,		//上移動.
		MoveDown,		//下移動.

		None = -1,		//未設定.
	};
public:
	CPlayer();
	~CPlayer();

	//動作関数.
	void Update() override;	//override:再定義前の関数が仮想関数かチェックできる.
							//		   仮想関数でない場合はエラーになる.
	//描画関数.
	void Draw( CCamera* pCamera ) override;

	void HIT();

	void SetImageLEFT(CImage* sh) { LEFTImg = sh; }

	void SetImageEX(CImage* sh) { PEXP_IMG = sh; }

private:
	//操作処理.
	void KeyInput();
	//アニメーション処理.
	/*void Animation();*/

private:
	int			m_GroundPos;	//地面の位置(定数でも可).
	CImage*     LEFTImg;
	CImage*     PEXP_IMG;
	VECTOR2		m_OldPosition;	//移動前の位置.
	int			m_Action;		//動作状態.
	int         m_PlayerLEFT;
	
	//ジャンプ処理.
	bool		m_Jumping;	//ジャンプ中.
	bool        Invicible;
	int         Inviciblecnt;
	float		m_JumpAcc;	//加速度:Acceleration(ジャンプ減速用).
	float		m_JumpPower;//ジャンプ力(定数でも可).
	float		m_Gravity;	//重力(定数でも可).
	int d;
};