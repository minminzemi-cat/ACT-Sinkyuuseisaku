#pragma once
#include "CCamera.h"	//カメラクラス.

/**************************************************
*	ゲームオブジェクト.
*	継承することを前提としたクラス.
**/
class CGameObject
{
public:
	CGameObject() {}
	virtual ~CGameObject() {}

	//純粋仮想関数:関数の引数より後ろに「= 0」を付ける.
	//			  このクラスで定義を作成せず、継承先のクラスで作成する.
	//			  継承先で定義を作成しなかった場合はエラーになる.
	virtual void Update() = 0;
	virtual void Draw( CCamera* pCamera ) = 0;
	//ステータスを取得する
	int GetPlayerStetus() { return m_PlayerState; }

	int					 m_PlayerState;	//プレイヤーの生存確認


private:
	
};