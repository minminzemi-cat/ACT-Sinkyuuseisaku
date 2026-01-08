#pragma once
#include"CImage.h"
#include "CCamera.h"	//カメラクラス.
#include "MyMath.h"	
#include"Global.h"



class CTimer
{
public:
	CTimer();
	~CTimer();



public:

	//画像を読み込む関数
	void SetImage(CImage* pImg) { m_TimerImg = pImg; }


	//int time　には、経過した時間が入っている

	void Update(int times);

	//ゲームメインで残りの時間を表示
	void Draw(int x, int y,int times);


public:
	//クリアするまでのタイム,残り時間
	int kuriatime=5;

	//表示する残り時間
	int kuriaTimer;

	CImage* m_TimerImg;

	


};