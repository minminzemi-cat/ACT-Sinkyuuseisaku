#include "GameOver.h"
#include "Result.h"

CResult::CResult()
{
	//Rank_SOLDIER    = false;
	//Rank_KNIGHT		= false;	
	//Rank_HERO		= false;
	//Rank_LEGEND		= false;
	//Rank_ZOMBIE		= false;
	//Rank_Shooter	= false;
	//Rank_SWORDSAINT	= false;
	//Rank_SLAYER		= false;
	//Rank_MG_PEACE	= false;
}

CResult::~CResult()
{
}

void CResult::Update()
{
	if (m_enemy->GetKill() >= 4 
		&& exc->GetEXUse() == true)
	{
		m_Rank = enRank::SOLDIER;
	}
	if (m_enemy->GetKill() >= 10
		&& exc->GetEXUse() == true)
	{
		m_Rank = enRank::KNIGHT;
	}
	if (m_enemy->GetKill() >= 20
		&& exc->GetEXUse() == true)
	{
		m_Rank = enRank::HERO;
	}
	if (m_enemy->GetKill() >= 50
		&&exc->GetEXUse() == true)
	{
		m_Rank = enRank::LEGEND;
	}

	if (m_enemy->GetKill() <=5
		&& exc->GetEXUse() == true)
	{
		
		m_Rank = enRank::MG_PEAC;
	}

	if (exc->GetEXUse()==false)
	{
		
		m_Rank = enRank::Shooter;
	}


}

void CResult::Draw(CCamera* pCamera)
{
	ResultIMG->TransBlt(0, 0, 480, 640, 0, 0);

	m_Score->ResultDraw(350, 460, score);



	switch (m_Rank)
	{
	case enRank::SOLDIER:
		RankIMG->TransBlt(100, 200, 210, 100, 0, 0);
		break;
	case enRank::KNIGHT:
		RankIMG->TransBlt(100, 200, 210, 100, 218, 0);
		break;
	case enRank::HERO:
		RankIMG->TransBlt(100, 200, 210, 100, 436, 0);
		break;
	case enRank::LEGEND:
		RankIMG->TransBlt(100, 200, 210, 100, 684, 0);
		break;	
	case enRank::Shooter:
		RankIMG->TransBlt(100, 200, 210, 100, 1490, 0);
		break;
	case enRank::MG_PEAC:
		RankIMG->TransBlt(100, 200, 250, 100, 1940, 0);
		break;
	//case enRank::MG_PEAC:
	//	RankIMG->TransBlt(100, 200, 210, 200, 684, 0);
	//	break;

	default:
		break;
		
	}

}