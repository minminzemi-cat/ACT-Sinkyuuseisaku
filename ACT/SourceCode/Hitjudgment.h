#pragma once

/****************************************
*		当たり判定クラス（地獄）
*******************************************/

class CHitjudgment
{
public:
	CHitjudgment();

	~CHitjudgment();

	bool collisionDetection(
		int Ax, int Ay, int Aw, int Ah,			//矩形Aの座標と高さ
		int Bx, int By, int Bw, int Bh);


	bool collisionSpher(
		int r1x, int r1y, int Aw, int Ah,			//矩形Aの座標と高さ
		int r2x, int r2y, int Bw, int Bh);


protected:
};

