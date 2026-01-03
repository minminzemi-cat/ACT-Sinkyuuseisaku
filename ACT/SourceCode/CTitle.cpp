#include"CTitle.h"

CTitle::CTitle()
	:m_pSentakuImg(nullptr)
	, m_TitleSword(290)
{
}

CTitle::~CTitle()
{

}




//選択肢の描画関数
void CTitle::Draw(CCamera* pCamera)
{

	

	//ゲームスタート
	m_pSentakuImg->TransBlt(
		140,					//表示位置x座標
		300,					//表示位置y座標.
		200,				//画像幅
		70,					//画像高さ.
		0,					//元画像x座標.・・・座標0,0から画像幅、高さ分を取り出しますよ
		0);					//元画像y座標.

	
	//ゲーム終了
	m_pSentakuImg->TransBlt(
		140,					//表示位置x座標
		400,					//表示位置y座標.
		200,				//画像幅
		70,					//画像高さ.
		0,					//元画像x座標.・・・座標0,0から画像幅、高さ分を取り出しますよ
		170);					//元画像y座標.

}

//剣の描画
void CTitle::RDraw(CCamera* pCamera)
{

	m_pKennImg->TransBlt(
		50,					//表示位置x座標
		400,					//表示位置y座標.
		200,				//画像幅
		70,					//画像高さ.
		0,					//元画像x座標.・・・座標0,0から画像幅、高さ分を取り出しますよ
		170);					//元画像y座標.

}


//背景の描画
void CTitle::XDraw(CCamera* pCamera)
{
	m_pTitleBackImg->BBlt(
		0, 0,							//表示位置x,y座標.
		WND_W, WND_H,					//画像幅、高さ.
		0, 0);						//元画像x,y座標.
		

}


//動作関数
void CTitle::Update()
{
	////ゲームメインへ
	//if (m_TitleSword == 290)
	//{
	//	if (GetAsyncKeyState(VK_RETURN) & 0x0001 )
	//	{
	//		//m_Alpha = 0;		//次にタイトルに入ってきても大丈夫なように最小値を設定						

	//		m_Game->m_Scene = enScene::GameMain;	//ゲームメインへ

	//		
	//	}
	//}
	////ゲーム終了
	//if (m_TitleSword == 395)
	//{
	//	if (GetAsyncKeyState(VK_RETURN) & 0x0001 )
	//	{
	//		PostMessage(m_pGameWnd->hWnd, WM_CLOSE, 0, 0);

	//	}
	//}

	if (GetAsyncKeyState(VK_UP) & 0x0001)//アップキー
	{
		//剣が画面買いに行かないようにする処理
		if (m_TitleSword > 290) {
			//剣の画像がアップキーを押された場合どのような動きをするか
			m_TitleSword -= 105;
		}

	}


	if (GetAsyncKeyState(VK_DOWN) & 0x0001)//ダウンキー
	{
		//剣が画面外にいかないようにする処理
		if (m_TitleSword < 500) {

			m_TitleSword += 105;

		}

	}

}



