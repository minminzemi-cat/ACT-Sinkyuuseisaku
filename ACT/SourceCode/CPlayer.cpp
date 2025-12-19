#include "CPlayer.h"
#include "Global.h"
#include "CSoundManager.h"	//サウンドマネージャクラス.

CPlayer::CPlayer()
	: m_GroundPos	( WND_H - 64 )
	, m_OldPosition	()
	, m_Action		( enAction::Wait )
	, m_Jumping		( false )
	, m_JumpAcc		( 0.0f )
	, m_JumpPower	( 24.0f )	//値を変えるとジャンプの高さが変わる.
	, m_Gravity		( 0.8f )	//値を変えると落下速度が変わる.
{
	m_Position = VECTOR2( 0, m_GroundPos );
	m_MoveSpeed = 4;
	m_PlayerState = enCharaState::Living;
	Invicible = false;
	Inviciblecnt = 0;
	d = 0;
	m_PlayerLEFT = 3;
}
 
CPlayer::~CPlayer()
{
}

//動作関数.
void CPlayer::Update()
{
	//移動前の位置を退避.
	m_OldPosition = m_Position;

	//毎フレーム最初は待機状態に戻す.
	m_Action = enAction::Wait;

	KeyInput();


	//動作状態による処理の場合分け.
	//switch( m_Action ){
	//case enAction::Wait:
	//	break;
	//case enAction::MoveLeft:
	//	
	//	m_LookingRight = false;	//右向き無効.
	//	break;
	//case enAction::MoveRight:
	//
	//	m_LookingRight = true;	//右向き有効.
	//	break;
	//case enAction::MoveUP:
	//
	//	break;
	//case enAction::MoveDown:
	//	m_Position.y += m_MoveSpeed;
	//	break;
	//case enAction::None:
	//	break;
	//default:
	//	break;
	//}
}

//描画関数.
void CPlayer::Draw( CCamera* pCamera )
{
	for (int pNo = 0; pNo <= 15; pNo++)
	{
		if (m_PlayerState == enCharaState::Living/*&& Invicible == false*/)
		{
			//アニメーション処理.
			/*Animation();*/
			m_FrameSplit.w = 64;
			m_FrameSplit.h = 64;
			m_FrameSplit.x = 0;
			m_FrameSplit.y = 0;

			VECTOR2 DispPos = pCamera->CalcToPositionInCamera(&m_Position, &m_FrameSplit);

			//自機の表示.
			m_pImg->TransBlt(
				DispPos.x,			//表示位置x座標.
				DispPos.y,			//表示位置y座標.
				m_FrameSplit.w,		//画像幅.
				m_FrameSplit.h,		//画像高さ.
				m_FrameSplit.x,		//元画像のx座標.
				m_FrameSplit.y);	//元画像のy座標.
		}
		else if (m_PlayerState == enCharaState::Deading)
		{
			PEXP_IMG->TransBlt(
				m_Position.x,
				m_Position.y,
				128,
				128,
				(m_PlayerExpAnimCnt % 12) * 128,
				0);
		}
		if (m_PlayerState == enCharaState::Deading)
		{
			m_PlayerExpAnimCnt++;
			if (m_PlayerExpAnimCnt >= 30)
			{
				m_PlayerState = enCharaState::Dead;
			}
			break;
		}

		//if(Invicible == true&& m_PlayerState == enCharaState::Living)
		//{
		//	//アニメーション処理.
		//	/*Animation();*/
		//	m_FrameSplit.w = 64;
		//	m_FrameSplit.h = 64;
		//	m_FrameSplit.x = 0;
		//	m_FrameSplit.y = 64;

		//	VECTOR2 DispPos = pCamera->CalcToPositionInCamera(&m_Position, &m_FrameSplit);

		//	//自機の表示.
		//	m_pImg->TransAlBlend(
		//		DispPos.x,			//表示位置x座標.
		//		DispPos.y,			//表示位置y座標.
		//		m_FrameSplit.w,		//画像幅.
		//		m_FrameSplit.h,		//画像高さ.
		//		m_FrameSplit.x,		//元画像のx座標.
		//		m_FrameSplit.y,
		//		300);	//元画像のy座標.
		//}



		for (int i = 0; i < m_PlayerLEFT; i++)
		{
			LEFTImg->TransAlBlend(128 + 32 * i, 560, 32, 32, (64 * 2) + 32, 64, 127);

		}
	}

}

void CPlayer::HIT()
{


	Inviciblecnt++;
	if (Invicible != true)
	{
		m_PlayerLEFT -= 1;

		m_Position.x = (WND_W / 2) - (64 / 2);
		m_Position.y = 550;
	}

	if (Inviciblecnt <= 50)
	{
		Invicible = true;
	}
	else if (Inviciblecnt >= 50)
	{
		Invicible = false;
		Inviciblecnt = 0;
	}

	if (m_PlayerLEFT==0) {
		m_PlayerState = enCharaState::Deading;
		CSoundManager::PlaySE(CSoundManager::enList::SE_Dead);
	}
}

//操作処理.
void CPlayer::KeyInput()
{
	
	//←.
	if( GetAsyncKeyState( VK_LEFT ) & 0x8000 && m_Position.x > 0)//0x0001[遅延連射], 0x8000[即連射].
	{
		m_Position.x -= m_MoveSpeed;
	}
	//→.
	if( GetAsyncKeyState( VK_RIGHT ) & 0x8000 && m_Position.x <= WND_W - 64)//0x0001[遅延連射], 0x8000[即連射].
	{
		m_Position.x += m_MoveSpeed;
	}
	//↑
	if (GetAsyncKeyState(VK_UP) & 0x8000 && m_Position.y > 0)//0x0001[遅延連射], 0x8000[即連射].
	{
		m_Position.y -= m_MoveSpeed;
	}
	//↓
	if (GetAsyncKeyState(VK_DOWN) & 0x8000 && m_Position.y <= WND_H - 64)//0x0001[遅延連射], 0x8000[即連射].
	{
		m_Position.y += m_MoveSpeed;
	}
	if (GetAsyncKeyState('C') & 0x8000)//0x0001[遅延連射], 0x8000[即連射].
	{
	
	}

}

////アニメーション処理.
//void CPlayer::Animation()
//{
//	//常にカウンタを動かす.
//	m_FrameCounter++;
//
//	m_FrameSplit.w = 32;
//	m_FrameSplit.h = 64;
//	m_FrameSplit.y = 0;
//
//	switch( m_Action )
//	{
//	case enAction::Wait:		//待機.
//		m_FrameSplit.x = 0;	//待機画像(0コマ目).
//		m_FrameCounter = 0;	//待機アニメーションないので0にしておく.
//		break;
//	case enAction::MoveLeft:	//左移動.
//	case enAction::MoveRight:	//右移動.
//		//F6(6フレーム)ごとにアニメーション切り替え.
//		if( m_FrameCounter >= 6 ){
//			m_FrameSplit.x += m_FrameSplit.w;
//			m_FrameCounter = 0;	//カウンタの初期化.
//		}
//
//		//歩きアニメーション最大コマ数(1コマ目)を超えると最初(0コマ目)に戻す.
//		if( m_FrameSplit.x / m_FrameSplit.w > 1 )
//		{
//			m_FrameSplit.x = 0;	//アニメーション開始位置(0コマ目)に戻す.
//		}
//		break;
//	case enAction::None:		//未設定.
//		break;
//	default:
//		break;
//	}
//
//
//
//	//右向き判定.
//	if( m_LookingRight == true )
//	{
//		m_FrameSplit.y += m_FrameSplit.h;
//	}
//}