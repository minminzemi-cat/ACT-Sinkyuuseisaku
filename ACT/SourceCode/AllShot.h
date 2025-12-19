#pragma once
#include "CGameObject.h"	//ゲームオブジェクトクラス.
#include "CImage.h"			//画像クラス.
#include "MyMath.h"			//数学クラス.


/**************************************************
*   キャラクタークラス.
**/
class AllShot

		
{
public:
	AllShot();
	//仮想関数:関数の戻り値の型の前に virtual をつける.
	//		  継承させる可能性のあるクラスのデストラクタは仮想関数にすること.
	virtual ~AllShot();

	virtual void UpdateShot() {};
	virtual void DrawShot(CCamera* pCamera) {};

	//画像を設定する.
	void SetImage(CImage* pImg) { m_pImg = pImg; }
	void SetPos(VECTOR2 Pos) { m_SPsPosition = Pos; }


	//位置を取得する.
	VECTOR2 GetPsPosition() const { return m_PsPosition[PS_MAX]; }
	VECTOR2 GetBsPosition() const { return m_BsPos; }
	VECTOR2 GetSPPosition() const { return m_SPsPosition; }

	//１コマの画像情報を取得する.
	CImage::FRAMESPLIT GetFrameSplit() const { return m_FrameSplit; }
	
	int m_SpAnimCnt;
protected:  //protected:外部アクセス不可能.派生クラスでアクセス可能.
	CImage*		m_pImg;		
	CImage::FRAMESPLIT	m_FrameSplit;	//１コマの画像情報.
	int					m_FrameCounter;	//アニメーション制御用カウンタ.
	static const int		PS_MAX = 15;
	static const int		BS_MAX = 1;
	VECTOR2		m_PsPosition[PS_MAX];
	VECTOR2		m_BsPosition[BS_MAX];
	VECTOR2		m_SPsPosition;
	VECTOR2		m_GeagPosition;
	VECTOR2     m_KenPosition;
	VECTOR2 m_BsPos;
	VECTOR2      m_bomsetPosition;//ボム位置
	bool				m_LookingRight;	//右向き判定.

};