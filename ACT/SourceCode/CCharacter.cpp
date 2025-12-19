#include "CCharacter.h"

CCharacter::CCharacter()
	: m_pImg		( nullptr )

	, m_MoveSpeed	( 4 )
	, m_MoveSrowSpeed( 3 )
	, m_FrameSplit	()
	, m_FrameCounter( 0 )
	, m_LookingRight( false )
	, m_Score(0)
{

}

CCharacter::~CCharacter()
{
	//ŠO•”‚Åì¬‚³‚ê‚½‚à‚Ì‚È‚Ì‚Å‚±‚±‚Å‚Í”jŠü‚µ‚È‚¢.
	m_pImg = nullptr;
}