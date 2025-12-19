#define _USE_MATH_DEFINES
#include "CImage2.h"
#include <cmath>
#include "Global.h"
//透過色(緑を指定).
const UINT TRANS_COLOR RGB(0x00, 0xFF, 0x00);


CImage::CImage(HDC	m_hScreenDC, HDC	m_hMemDC,HDC mhWorkDC, HDC mhWorkDC2)
	:m_hBmp(nullptr)
	, m_hScreenDC(m_hScreenDC)
	, m_hMemDC(m_hMemDC)
	, m_hWorkDC(mhWorkDC)
	, m_hWorkDC2(mhWorkDC2)
{
}

CImage::~CImage()
{
	DeleteObject(m_hBmp);

	//外部で作られたものなのでnullptrで初期化
	m_hWorkDC = nullptr;
	m_hMemDC = nullptr;
	m_hScreenDC = nullptr;
}
//画像の読み込み.
bool CImage::LoadBmp(  const char* fileName )
{
	m_hBmp = (HBITMAP)LoadImage(
		nullptr,			//インスタンス.
		fileName,			//ファイル名(パス含む).
		IMAGE_BITMAP,		//ビットマップ.
		0, 0,				//読み込む座標.
		LR_LOADFROMFILE );	//ファイルから読み込む.

	if(m_hBmp == nullptr ){
		MessageBox( nullptr,
			fileName, "画像読み込み失敗", MB_OK );
		return false;
	}
	return true;
}
//画像を表示する関数
bool CImage::BBLt(int xDest, int yDest, int wDest, int hDest, int xSrc, int ySrc)
{
	SelectObject(m_hMemDC, m_hBmp);

	if (BitBlt(
		m_hScreenDC,
		xDest, yDest,
		wDest, hDest,
		m_hMemDC,
		xSrc, ySrc,
		SRCCOPY) == FALSE) {
		return false;
	}
	
	return true;
}

//画像を透過して表示.
bool CImage::TransBlt(  int xDest, int yDest,
	int wDest, int hDest, int xSrc, int ySrc )
{
	
	SelectObject(m_hMemDC, m_hBmp);
	if( TransparentBlt(
		m_hScreenDC,			//表	示先(実はディスプレイ).
		xDest, yDest,		//表示位置x,y座標.
		wDest, hDest,		//表示幅、高さ.
		m_hMemDC,				//画像が設定されたメモリDC.
		xSrc, ySrc,			//元画像の取り出し開始x,y座標.
		wDest, hDest,		//元画像の取り出し幅、高さ.
		TRANS_COLOR)//透過色(緑を指定).
		== FALSE )
	{
		return false;
	}
	return true;
}
//画像を透過して表示.
bool CImage::TransBltplas(int xDest, int yDest,
	int wDest, int hDest, int xSrc, int ySrc, int wSrc, int hSrc )
{

	SelectObject(m_hMemDC, m_hBmp);
	if (TransparentBlt(
		m_hScreenDC,			//表	示先(実はディスプレイ).
		xDest, yDest,		//表示位置x,y座標.
		wDest, hDest,		//表示幅、高さ.
		m_hMemDC,				//画像が設定されたメモリDC.
		xSrc, ySrc,			//元画像の取り出し開始x,y座標.
		wSrc, hSrc,		//元画像の取り出し幅、高さ.
		TRANS_COLOR)//透過色(緑を指定).
		== FALSE)
	{
		return false;
	}
	return true;
}

//画像半透明にして表示する関数
bool CImage::AlBlend(int xDest, int yDest, int wDest, int hDest,
	 int xSrc, int ySrc, int Alpha) {

	
	//BLENDFUNCTION構造体
	BLENDFUNCTION blendfunc = { AC_SRC_OVER, 0, (BYTE)Alpha, 0 };
	SelectObject(m_hMemDC, m_hBmp);
	if (AlphaBlend(
		m_hScreenDC,			//表	示先(実はディスプレイ).
				//表示先(実はﾃﾞｨｽﾌﾟﾚｲ)
		xDest, yDest,		//表示位置x座標.y座標
		wDest, hDest,		//表示幅,高さ
		m_hMemDC,			//画像が設定されたﾒﾓﾘDC
		xSrc, ySrc,////元画像の取り出し開始x,y座標
		wDest, hDest,//読み込み画像元、高さ
		blendfunc))//BLENDFUNCTION構造体
	{
		return true;
	}
	return false;
}
//画像を透過+画像半透明にして表示する関数
void CImage::TransAlBlend(int xDest, int yDest,
	int wDest, int hDest,
	int xSrc, int ySrc, int Alpha)
{
	//t敵の表示
	int x = 0; int y = 0;
	SelectObject(m_hMemDC,m_hBmp);
	//スクリーン→作業用DCへ
	BitBlt(
		m_hWorkDC,//出力先：作業用DC
		0, 0,//出力先：x,y,は０固定
		wDest, hDest,
		m_hScreenDC,//読み込み元：スクリーン
		xDest, yDest,//スクリーン上で表示したい」ｘｙざひょう
		SRCCOPY);
	//メモリ→作業用DCへ
	TransparentBlt(
		m_hWorkDC,//出力先：作業用DC
		0, 0,
		wDest, hDest,
		m_hMemDC,//読み込み元：メモリ
		xSrc,
		ySrc,
		wDest, hDest,
		TRANS_COLOR);
	//作業用DC→スクリーンへ
	BLENDFUNCTION blendfunc = { AC_SRC_OVER, 0,(BYTE)Alpha, 0 };
	AlphaBlend(
		m_hScreenDC,//出力先：スクリーン
		xDest, yDest,
		wDest, hDest,
		m_hWorkDC,//読み込み元：作業用DC
		0, 0,
		wDest, hDest,
		blendfunc
	);
}
void CImage::TransAlBlendplas(int xDest, int yDest, int wDest, int hDest, int xSrc, int ySrc, int wSrc, int hSrc, int Alpha)
{
	SelectObject(m_hMemDC, m_hBmp);
	//スクリーン→作業用DCへ
	BitBlt(
		m_hWorkDC,//出力先：作業用DC
		0, 0,//出力先：x,y,は０固定
		wDest, hDest,
		m_hScreenDC,//読み込み元：スクリーン
		xDest, yDest,//スクリーン上で表示したい」ｘｙざひょう
		SRCCOPY);
	//メモリ→作業用DCへ
	TransparentBlt(
		m_hWorkDC,//出力先：作業用DC
		0, 0,
		wDest, hDest,
		m_hMemDC,//読み込み元：メモリ
		xSrc,
		ySrc,
		wSrc, hSrc,
		TRANS_COLOR);
	//作業用DC→スクリーンへ
	BLENDFUNCTION blendfunc = { AC_SRC_OVER, 0,(BYTE)Alpha, 0 };
	AlphaBlend(
		m_hScreenDC,//出力先：スクリーン
		xDest, yDest,
		wDest, hDest,
		m_hWorkDC,//読み込み元：作業用DC
		0, 0,
		wDest, hDest,
		blendfunc
	);

}


void CImage::TransSpinAlBltplas(double SenterX, double SenterY, double wDest, double hDest, int xSrc, int ySrc, int wSrc, int hSrc, int C, int Alpha)
{
	SelectObject(m_hMemDC, m_hBmp);


	BitBlt(
		m_hWorkDC,//出力先：作業用DC
		0, 0,//出力先：x,y,は０固定
		WND_W, WND_H,
		m_hScreenDC,//読み込み元：スクリーン
		0, 0,//スクリーン上で表示したい」ｘｙざひょう
		SRCCOPY);
	BitBlt(
		m_hWorkDC2,//出力先：作業用DC
		0, 0,//出力先：x,y,は０固定
		WND_W, WND_H,
		m_hScreenDC,//読み込み元：スクリーン
		0, 0,//スクリーン上で表示したい」ｘｙざひょう
		SRCCOPY);


	POINT   po[3];
	double a = M_PI / 180;

	po[0].x = (((-wDest / 2) * cos(C * a) - (-hDest / 2) * sin(C * a)) + SenterX);
	po[0].y = (((-wDest / 2) * sin(C * a) + (-hDest / 2) * cos(C * a)) + SenterY);
	po[1].x = (((wDest / 2) * cos(C * a) - (-hDest / 2) * sin(C * a)) + SenterX);
	po[1].y = (((wDest / 2) * sin(C * a) + (-hDest / 2) * cos(C * a)) + SenterY);
	po[2].x = (((-wDest / 2) * cos(C * a) - (hDest / 2) * sin(C * a)) + SenterX);
	po[2].y = (((-wDest / 2) * sin(C * a) + (hDest / 2) * cos(C * a)) + SenterY);


	//	PlgBlt(m_hWorkDC, po, m_hMemDC, wSrc * xSrc, 0, wSrc, hSrc, NULL, 0, 0);
	PlgBlt(m_hWorkDC, po, m_hMemDC, xSrc, ySrc, wSrc, hSrc, NULL, 0, 0);
	//メモリ→作業用DCへ

	TransparentBlt(
		m_hWorkDC2,//出力先：作業用DC
		0, 0,
		WND_W, WND_H,
		m_hWorkDC,//読み込み元：メモリ
		0,
		0,
		WND_W, WND_H,
		TRANS_COLOR);

	//作業用DC→スクリーンへ
	BLENDFUNCTION blendfunc = { AC_SRC_OVER, 0,(BYTE)Alpha, 0 };
	AlphaBlend(
		m_hScreenDC,//出力先：スクリーン
		0, 0,
		WND_W, WND_H,
		m_hWorkDC2,//読み込み元：作業用DC
		0, 0,
		WND_W, WND_H,
		blendfunc
	);
}







void CImage::TransSpinBltplas(double xDest, double yDest, double wDest, double hDest, int xSrc, int ySrc, int wSrc, int hSrc, int C)
{
	SelectObject(m_hMemDC, m_hBmp);


	BitBlt(
		m_hWorkDC,//出力先：作業用DC
		0, 0,//出力先：x,y,は０固定
		wDest, hDest,
		m_hScreenDC,//読み込み元：スクリーン
		xDest, yDest,//スクリーン上で表示したい」ｘｙざひょう
		SRCCOPY);



	POINT   po[3];
	double a = M_PI / 180;

	po[0].x = ((xDest - (xDest + wDest / 2)) * cos(C * a) - (yDest - (yDest + hDest / 2)) * sin(C * a)) + wDest / 2;
	po[0].y = ((xDest - (xDest + wDest / 2)) * sin(C * a) + (yDest - (yDest + hDest / 2)) * cos(C * a)) + hDest / 2;
	po[1].x = ((xDest + wDest - (xDest + wDest / 2)) * cos(C * a) - (yDest - (yDest + hDest / 2)) * sin(C * a)) + wDest / 2;
	po[1].y = ((xDest + wDest - (xDest + wDest / 2)) * sin(C * a) + (yDest - (yDest + hDest / 2)) * cos(C * a)) + hDest / 2;
	po[2].x = ((xDest - (xDest + wDest / 2)) * cos(C * a) - (yDest + hDest - (yDest + hDest / 2)) * sin(C * a)) + wDest / 2;
	po[2].y = ((xDest - (xDest + wDest / 2)) * sin(C * a) + (yDest + hDest - (yDest + hDest / 2)) * cos(C * a)) + hDest / 2;


	PlgBlt(m_hWorkDC, po, m_hMemDC, wSrc * xSrc, hSrc* ySrc, wSrc, hSrc, NULL, 0, 0);

	//メモリ→作業用DCへ

	TransparentBlt(
		m_hScreenDC,//出力先：作業用DC
		xDest, yDest,
		wDest, hDest,
		m_hWorkDC,//読み込み元：メモリ
		0,
		0,
		wDest, hDest,
		TRANS_COLOR);


}

void CImage::TransSpinBltplasplas(double xDest, double yDest, double wDest, double hDest, int xSrc, int ySrc, int wSrc, int hSrc, int C)
{
	SelectObject(m_hMemDC, m_hBmp);


	BitBlt(
		m_hWorkDC,//出力先：作業用DC
		0, 0,//出力先：x,y,は０固定
		WND_W, WND_H,
		m_hScreenDC,//読み込み元：スクリーン
		0, 0,//スクリーン上で表示したい」ｘｙざひょう
		SRCCOPY);



	POINT   po[3];
	double a = M_PI / 180;

	po[0].x = (((xDest - (xDest + wDest / 2)) * cos(C * a) - (yDest - (yDest + hDest / 2)) * sin(C * a)) +  xDest + wDest / 2)	;
	po[0].y = (((xDest - (xDest + wDest / 2)) * sin(C * a) + (yDest - (yDest + hDest / 2)) * cos(C * a)) + yDest + hDest / 2)	;
	po[1].x = (((xDest + wDest - (xDest + wDest / 2)) * cos(C * a) - (yDest - (yDest + hDest / 2)) * sin(C * a))+ xDest + wDest / 2) ;
	po[1].y = (((xDest + wDest - (xDest + wDest / 2)) * sin(C * a) + (yDest - (yDest + hDest / 2)) * cos(C * a))+ yDest + hDest / 2) ;
	po[2].x = (((xDest - (xDest + wDest / 2)) * cos(C * a) - (yDest + hDest - (yDest + hDest / 2)) * sin(C * a))+ xDest + wDest / 2) ;
	po[2].y = (((xDest - (xDest + wDest / 2)) * sin(C * a) + (yDest + hDest - (yDest + hDest / 2)) * cos(C * a))+ yDest + hDest / 2) ;


//	PlgBlt(m_hWorkDC, po, m_hMemDC, wSrc * xSrc, 0, wSrc, hSrc, NULL, 0, 0);
	PlgBlt(m_hWorkDC, po, m_hMemDC,  xSrc,  ySrc, wSrc, hSrc, NULL, 0, 0);
	//メモリ→作業用DCへ

	TransparentBlt(
		m_hScreenDC,//出力先：作業用DC
		0, 0,
		WND_W, WND_H,
		m_hWorkDC,//読み込み元：メモリ
		0,
		0,
		WND_W, WND_H,
		TRANS_COLOR);

}
	