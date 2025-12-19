#include "GameOver.h"

CGameOver::CGameOver()
{
}

CGameOver::~CGameOver()
{
}

void CGameOver::Update()
{

}

void CGameOver::Draw(CCamera* pCamera)
{
	GameOverIMG->TransBlt(0, 0, 480, 640, 0, 0);
}