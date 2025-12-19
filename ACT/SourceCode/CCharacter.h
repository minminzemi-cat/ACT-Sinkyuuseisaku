#pragma once
#include "CGameObject.h"	//ゲームオブジェクトクラス.
#include "CImage.h"			//画像クラス.
#include "MyMath.h"			//数学クラス.


/**************************************************
*   キャラクタークラス.
**/
class CCharacter
	: public CGameObject	//ゲームオブジェクトクラスを継承.
{
public:
	//動作状態列挙型
	enum enCharaState
	{
		Living,
		Dead,
		Deading,
		Standby,
	};
	CCharacter();
	//仮想関数:関数の戻り値の型の前に virtual をつける.
	//		  継承させる可能性のあるクラスのデストラクタは仮想関数にすること.
	virtual ~CCharacter();


	virtual void Update()override {}
	virtual void Draw( CCamera* pCamera )override {}


	//画像を設定する.
	void SetImage( CImage* pImg ) { m_pImg = pImg; }
	
	VECTOR2 GetPosition(){ return m_Position; }

	//ステータスを取得する
	int GetPlayerStetus() { return m_PlayerState; }
	int GetEnemyStetus () { return m_EnemyState; }
	int GetEnemyStetus2() { return m_EnemyState2; }
	int	GetKill()		  { return m_Killcnt; }
	//int	GetSP()			  { return SP; }
	int					 m_PlayerState;	//プレイヤーの生存確認
	int					 m_EnemyState;	//プレイヤーの生存確認
	int					 m_EnemyState2;	//プレイヤーの生存確認
	int                  m_PlayerExpAnimCnt;
	
	

protected:  //protected:外部アクセス不可能.派生クラスでアクセス可能.
	CImage* m_pImg;			//画像(外部で読み込んだデータを入れる).
	VECTOR2		m_Position;		//位置(座標).
	int			m_MoveSpeed;	//移動速度.
	int			m_MoveSrowSpeed;	//移動速度.
	int         m_Killcnt;                  //罪を数えろ
	CImage::FRAMESPLIT	m_FrameSplit;	//１コマの画像情報.
	int					m_FrameCounter;	//アニメーション制御用カウンタ.
	bool				m_LookingRight;	//右向き判定.
	int                 m_Score;//スコア
	int					SP;

};