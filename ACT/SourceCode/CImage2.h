#pragma once
#include<windows.h>
#pragma comment( lib, "msimg32.lib" )	//指定色を透過して描画で使用する.
//半透明の描画でも使用する


/*
*イメージクラスを
*/

class CImage
{
public:
	CImage(HDC		m_hScreenDC,HDC		m_hMemDC	,HDC mhWorkDC, HDC mhWorkDC2);
	~CImage();

	//コマ割り構造体
	struct FRAMESPLIT {
		int x;//読み込みx座標
		int y;//読み込みy座標
		int w;//読み込み表示の幅
		int h;//読み込み表示の高さ

		FRAMESPLIT(int xSrc=0, int ySrc=0, int wDest=0,int hDest=0)
			:x(xSrc),y(ySrc),w(wDest),h(hDest)
		{}
	};

	//画像の読み込み.
	bool LoadBmp( const char* fileName);

	//画像を表示する関数
	bool BBLt(int xDest, int yDest,
		int wDest, int hDest, int xSrc, int ySrc);

	//画像を透過して表示.
	bool TransBlt( int xDest, int yDest,
		int wDest, int hDest,  int xSrc, int ySrc);


	bool TransBltplas(int xDest, int yDest,
		int wDest, int hDest, int xSrc, int ySrc, int wSrc, int hSrc);


	//画像半透明にして表示する関数
	bool AlBlend( int xDest, int yDest, int wDest, int hDest,
	 int xSrc, int ySrc, int Alpha);

	//画像を透過+画像半透明にして表示する関数
void TransAlBlend(int xDest, int yDest, int wDest, int hDest,
		int xSrc, int ySrc, int Alpha);
void TransAlBlendplas(int xDest, int yDest, int wDest, int hDest,
	int xSrc, int ySrc,int wSrc,int hSrc, int Alpha);

void TransSpinAlBltplas(double SenterX, double SenterY,   double  wDest, double  hDest, int xSrc,  int ySrc, int wSrc, int hSrc, int C, int Alpha);
void TransSpinBltplas(double  xDest, double  yDest, double  wDest, double  hDest, int xSrc, int ySrc, int wSrc, int hSrc, int C);

void TransSpinBltplasplas(double  xDest, double  yDest, double  wDest, double  hDest, int xSrc, int ySrc, int wSrc, int hSrc, int C);
	//ビットマップを取得する※一時的に作成したので消す
	HBITMAP getBmp()const { return m_hBmp; }

private:
	//delete「削除定義と呼ばれる関数」
	//指定された場合その関数はよび出せなくなる
	CImage() = delete;//デフォルトコンストラクター削除（使用禁止）
private:
	HBITMAP m_hBmp;

	HDC		m_hScreenDC;
	HDC		m_hMemDC;
	HDC		m_hWorkDC;//作業用DC
	HDC		m_hWorkDC2;//作業用DC
};

