#include "CCharacter.h"
#include "CGame.h"
#include "CSoundManager.h"	//サウンドマネージャクラス.
#include <time.h>			//time関数を使用するために必要.
//コンストラクタ.
CGame::CGame()
	: CGame( nullptr )
{
}

//コンストラクタ(引数あり).
CGame::CGame( GameWindow* pGameWnd )
	: m_pGameWnd	( pGameWnd )
	, m_hMemDC		( nullptr )
	, m_hWorkDC		( nullptr )
	, m_hWorkBmp	( nullptr )
	, m_hFont		( nullptr )
	, m_pBackImg	( nullptr )
	, m_pCharaImg	( nullptr )
	, m_pEnemyImg	( nullptr )
	, m_pPlayerImg	( nullptr )
	, m_pPShotImg   (nullptr)
	, m_pStageImg	( nullptr )
	, m_pEExprotionImg(nullptr)
	, m_pExprotionImg(nullptr)
	, m_pbossImg	(nullptr)
	, m_pbossHandImg(nullptr)
	, m_Player		()
	, m_pPlayer		( nullptr )
	, m_pEnemy		( nullptr )
	, m_pEnemy2		(nullptr)
	, m_pEnemy3		(nullptr)
	, m_pStage		( nullptr )
	, m_pCamera		( nullptr )
{
}

//デストラクタ.
CGame::~CGame()
{
}

//初期化(リセット)関数.
void CGame::InitializeGame()
{


}

//構築関数.
bool CGame::Create()
{
	m_scene = enScene::GameMain;
	//乱数の初期化.
	srand( (unsigned int)time( nullptr ) );

	//メモリDCの作成.
	m_hMemDC = CreateCompatibleDC( nullptr );

	//作業用DCの作成.
	m_hWorkDC = CreateCompatibleDC( m_pGameWnd->hScreenDC );                    //作業用DCの作成.
	m_hWorkBmp = CreateCompatibleBitmap( m_pGameWnd->hScreenDC, WND_W, WND_H ); //作業用BITMAPの作成.
	SelectObject( m_hWorkDC, m_hWorkBmp );                                      //DCとBITMAPを紐付け.


	//作業用DCの作成.
	m_hWorkDC2 = CreateCompatibleDC(m_pGameWnd->hScreenDC);                    //作業用DCの作成.
	m_hWorkBmp2 = CreateCompatibleBitmap(m_pGameWnd->hScreenDC, WND_W, WND_H); //作業用BITMAPの作成.
	SelectObject(m_hWorkDC2, m_hWorkBmp2);                                      //DCとBITMAPを紐付け.

	//フォントの作成.
	m_hFont = CreateFont(
		60,	//文字高さ.
		20,	//文字幅.
		0,	//角度.
		0,	//ベースライン角度.
		FW_REGULAR,	//太さ(太字:FW_BOLD,通常:FW_REGULAR).
		FALSE,		//斜体(TRUE:有効).
		FALSE,		//下線(TRUE:有効).
		FALSE,		//打ち消し線(TRUE:有効).
		SHIFTJIS_CHARSET,	//文字セット.
		OUT_DEFAULT_PRECIS,	//出力精度.
		CLIP_DEFAULT_PRECIS,//クリッピング精度.
		DEFAULT_QUALITY,	//出力品質.
		VARIABLE_PITCH | FF_ROMAN,	//可変ピッチとフォントファミリ.
		"HG創英角ﾎﾟｯﾌﾟ体" );		//書体(nullptr:現在使われている書体).


//--------------------------------
//プレイヤー
//-----------------------
	{
		m_pPlayerImg = new CImage(m_pGameWnd->hScreenDC, m_hMemDC, m_hWorkDC, m_hWorkDC2);
		//プレイヤー画像のインスタンス生成.
		m_pPLeftImg = new CImage(m_pGameWnd->hScreenDC, m_hMemDC, m_hWorkDC, m_hWorkDC2);
		//プレイヤーショット画像
		m_pPShotImg = new CImage(m_pGameWnd->hScreenDC, m_hMemDC, m_hWorkDC, m_hWorkDC2);
		//プレイヤーボムショット画像
		m_pBShotImg = new CImage(m_pGameWnd->hScreenDC, m_hMemDC, m_hWorkDC, m_hWorkDC2);
		//プレイヤーボム残り画像
		m_pBomSetImg = new CImage(m_pGameWnd->hScreenDC, m_hMemDC, m_hWorkDC, m_hWorkDC2);
		//プレイヤー剣残り画像
		m_pKenImg = new CImage(m_pGameWnd->hScreenDC, m_hMemDC, m_hWorkDC, m_hWorkDC2);
		//プレイヤー必殺画像
		m_pSPMoveImg = new CImage(m_pGameWnd->hScreenDC, m_hMemDC, m_hWorkDC, m_hWorkDC2);
		//プレイヤー必殺画像
		m_pSPImg = new CImage(m_pGameWnd->hScreenDC, m_hMemDC, m_hWorkDC, m_hWorkDC2);
		//プレイヤー必殺画像
		m_pSPGeagImg = new CImage(m_pGameWnd->hScreenDC, m_hMemDC, m_hWorkDC, m_hWorkDC2);
		//プライヤー爆発
		m_pExprotionImg = new CImage(m_pGameWnd->hScreenDC, m_hMemDC, m_hWorkDC, m_hWorkDC2);
	
	}

//--------------------------------
//エネミー
//-----------------------
	{
		//敵画像のインスタンス生成.
		m_pEnemyImg = new CImage(m_pGameWnd->hScreenDC, m_hMemDC, m_hWorkDC, m_hWorkDC2);
		//敵画像2のインスタンス生成.
		m_pEnemy2Img = new CImage(m_pGameWnd->hScreenDC, m_hMemDC, m_hWorkDC, m_hWorkDC2);


		//ボス

		m_pbossImg = new CImage(m_pGameWnd->hScreenDC, m_hMemDC, m_hWorkDC, m_hWorkDC2);

		m_pbossHandImg = new CImage(m_pGameWnd->hScreenDC, m_hMemDC, m_hWorkDC, m_hWorkDC2);

		m_pbossWayshotImg = new CImage(m_pGameWnd->hScreenDC, m_hMemDC, m_hWorkDC, m_hWorkDC2);

		m_pbossSlowshotImg = new CImage(m_pGameWnd->hScreenDC, m_hMemDC, m_hWorkDC, m_hWorkDC2);

		m_pbossbuiImg = new CImage(m_pGameWnd->hScreenDC, m_hMemDC, m_hWorkDC, m_hWorkDC2);

		//プライヤー爆発
		m_pEExprotionImg = new CImage(m_pGameWnd->hScreenDC, m_hMemDC, m_hWorkDC, m_hWorkDC2);
	}




//--------------------------------
//ステージ＆シーン関係
//-----------------------
	{
		//背景画像のインスタンス生成.
		m_pBackImg = new CImage(m_pGameWnd->hScreenDC, m_hMemDC, m_hWorkDC, m_hWorkDC2);

		//タイトルのインスタンス
		m_pTitleImg = new CImage(m_pGameWnd->hScreenDC, m_hMemDC, m_hWorkDC, m_hWorkDC2);

		//ゲームオーバー
		m_pOverImg = new CImage(m_pGameWnd->hScreenDC, m_hMemDC, m_hWorkDC, m_hWorkDC2);
		//エンディング
		m_pEndingImg = new CImage(m_pGameWnd->hScreenDC, m_hMemDC, m_hWorkDC, m_hWorkDC2);
		//リザルト画面
		m_pResultImg = new CImage(m_pGameWnd->hScreenDC, m_hMemDC, m_hWorkDC, m_hWorkDC2);
		//キャラクターのインスタンス生成.
		m_pCharaImg = new CImage(m_pGameWnd->hScreenDC, m_hMemDC, m_hWorkDC, m_hWorkDC2);
		//ステージ画像のインスタンス生成.
		m_pStageImg = new CImage(m_pGameWnd->hScreenDC, m_hMemDC, m_hWorkDC, m_hWorkDC2);
		//スコア画像のインスタンス生成.
		m_pscoreImg = new CImage(m_pGameWnd->hScreenDC, m_hMemDC, m_hWorkDC, m_hWorkDC2);
		//称号
		m_pRankImg = new CImage(m_pGameWnd->hScreenDC, m_hMemDC, m_hWorkDC, m_hWorkDC2);


	}


//------------------------------------------
//プレイヤー関係の画像
//--------------------------------
	{
		//プレイヤー画像の読み込み
		if (m_pPlayerImg->LoadBmp("Data\\Image\\cha.bmp") == false)  return false;
		//プレイヤー残基画像の読み込み
		if (m_pPLeftImg->LoadBmp("Data\\Image\\cha.bmp") == false)  return false;
		//プレイヤーショット画像の読み込み
		if (m_pPShotImg->LoadBmp("Data\\Image\\cha.bmp") == false)  return false;
		//プレイヤー爆発画像の読み込み
		if (m_pExprotionImg->LoadBmp("Data\\Image\\explosion.bmp") == false)  return false;
		//プレイヤーボムショット画像の読み込み
		if (m_pBShotImg->LoadBmp("Data\\Image\\cha.bmp") == false)  return false;
		//プレイヤー剣画像の読み込み
		if (m_pKenImg->LoadBmp("Data\\Image\\Ken.bmp") == false)  return false;
		//プレイヤー必殺画像の読み込み
		if (m_pSPMoveImg->LoadBmp("Data\\Image\\cha.bmp") == false)  return false;
		//プレイヤー必殺画像2の読み込み
		if (m_pSPImg->LoadBmp("Data\\Image\\SPATK2.bmp") == false)  return false;
		//プレイヤー必殺ゲージの読み込み
		if (m_pSPGeagImg->LoadBmp("Data\\Image\\Geag.bmp") == false)  return false;
	}

//------------------------------------------
//エネミー関係の画像
//--------------------------------
	{
		//敵画像の読み込み.
		if (m_pEnemyImg->LoadBmp("Data\\Image\\cha.bmp") == false)    return false;
		
		
		
		
		
		//ボス画像の読み込み.
		if (m_pbossImg->LoadBmp("Data\\Image\\boss.bmp") == false)    return false;
			
		//ボスの一部の画像の読み込み.
		if (m_pbossHandImg->LoadBmp("Data\\Image\\Mine.bmp") == false)    return false;

		//ボスの玉　way
		if(m_pbossWayshotImg->LoadBmp("Data\\Image\\way.bmp") == false)	return false;
		
		//ボスの玉 遅くする
		if (m_pbossSlowshotImg->LoadBmp("Data\\Image\\slow.bmp") == false)	return false;

		//ボスの玉　一部ぁら
		if (m_pbossbuiImg->LoadBmp("Data\\Image\\BossBui.bmp") == false)	return false;




		//敵画像の読み込み2.
		if (m_pEnemy2Img->LoadBmp("Data\\Image\\cha.bmp") == false)    return false;
	   //エネミー爆発画像の読み込み
	    if (m_pEExprotionImg->LoadBmp("Data\\Image\\Eexplosion.bmp") == false)  return false;
	} 

//------------------------------------------
//シーン関係＆ステージ関係の画像
//--------------------------------
	{

		//背景の読み込み.
		if (m_pBackImg->LoadBmp("Data\\Image\\back.bmp") == false) return false;





		//タイトル画像の読み込み
		if (m_pTitleImg->LoadBmp("Data\\Image\\sora2.bmp") == false) return false;

		//タイトル選択
		if (m_pSentakuImg->LoadBmp("Data\\Image\\sentaku.bmp") == false) return false;

		
		if (m_pKennImg->LoadBmp("Data\\Image\\Ken1.bmp") == false) return false;




		//ゲームオーバー.
		if (m_pOverImg->LoadBmp("Data\\Image\\GameOver.bmp") == false) return false;
		//ゲームクリア.
		if (m_pEndingImg->LoadBmp("Data\\Image\\Ending.bmp") == false) return false;
		//リザルト画面
		if (m_pResultImg->LoadBmp("Data\\Image\\Result.bmp") == false) return false;
		//リザルト2画面
		if (m_pRankImg->LoadBmp("Data\\Image\\Rank.bmp") == false) return false;
		//キャラクターの読み込み.
		if (m_pCharaImg->LoadBmp("Data\\BMP\\chara.bmp") == false) return false;
		//スコアの読み込み
		if (m_pscoreImg->LoadBmp("Data\\Image\\SCOAR.bmp") == false)  return false;
		//ステージ画像の読み込み
		if (m_pStageImg->LoadBmp("Data\\Image\\SwitchPlace_lite.bmp") == false)  return false;
	}


	//プレイヤーのインスタンス生成.
	m_pPlayer = new CPlayer();
	//画像の設定.
    m_pPlayer->SetImage( m_pPlayerImg );
	m_pPlayer->SetImageLEFT(m_pPLeftImg);
	m_pPlayer->SetImageEX(m_pExprotionImg);
	
	
	//プレイヤーショットのインスタンス生成
	m_ppshot = new PSHOT();
	//画像設定
	
	m_ppshot->SetImagePshot(m_pPShotImg);
	m_ppshot->SetImageBomset(m_pBomSetImg);
	m_ppshot->SetImageBshot(m_pBShotImg);
	m_ppshot->SetImageSP(m_pSPMoveImg);
	
	
	m_ppshot->SetPlayer(m_pPlayer);
	//m_ppshot->SetPos(m_pPlayer->GetPosition());


	m_Exc = new Exculibur();
	m_Exc->SetImageKen(m_pKenImg);
	m_Exc->SetPlayer(m_pPlayer);
	m_Exc->SetImageGeag(m_pSPGeagImg);
	m_Exc->SetImageSP2(m_pSPImg);
	m_Exc->SetEne(m_pEnemy);
	//エネミーのインスタンス生成.
	m_pEnemy = new CEnemy();
	//画像の設定.
	m_pEnemy->SetImage( m_pEnemyImg );
	m_pEnemy->SetImageEEX(m_pEExprotionImg);

	m_pEnemy2 = new CEnemy2();
	m_pEnemy2->SetImage(m_pEnemy2Img);


	//--------------ボスのインスタンス---------------
	m_pBoss = new CBoss();
	m_pBoss->SetImageBoss(m_pbossImg);
	m_pBoss->SetImageBOSSHand(m_pbossHandImg);
	m_pBoss->SetImageShot(m_pbossWayshotImg);
	m_pBoss->SetImageSlow(m_pbossSlowshotImg);
	m_pBoss->SetImagebui(m_pbossbuiImg);

	//ステージのインスタンス生成.
	m_pStage = new CStage();
	//画像の設定.
	m_pStage->SetImage( m_pStageImg );
	m_pStage->SetImageBack(m_pBackImg);
	m_pStage->SetImageScore(m_pscoreImg);
	////マップデータ読み込み.
	//if( m_pStage->LoadData( "Data\\MapData\\Map01.csv" ) == false ) return false;






	//タイトルのインスタンス生成
	m_pTitle=new CTitle();
	m_pTitle->SetImageTitle(m_pSentakuImg);
	m_pTitle->SetImageBack(m_pTitleImg);
	m_pTitle->SetImageSord(m_pKennImg);




	//ゲームオーバーのインスタンス生成.
	m_GameOver = new CGameOver();
	m_GameOver->SetImageGameOver(m_pOverImg);

	//ゲームオーバーのインスタンス生成.
	m_GameOver = new CGameOver();
	m_GameOver->SetImageGameOver(m_pOverImg);

	//ゲームクリアのインスタンス生成.
	m_Ending = new CEnding();
	m_Ending->SetImageEnding(m_pEndingImg);


	//リザルト画面のいんすたんすせいせい　
	m_result = new CResult();
	m_result->SetImageResult(m_pResultImg);
	m_result->SetImageRank(m_pRankImg);
	m_result->SetEn(m_pEnemy);
	m_result->SetEx(m_Exc);
	//m_result->SetImagecgame(m_cgame);


	//カメラのインスタンス生成.
	m_pCamera = new CCamera();
	m_pCamera->SetStageWidth( m_pStage->GetWidth() );

	//サウンドデータを読み込む.
	if( CSoundManager::GetInstance()->Load( m_pGameWnd->hWnd ) == false ) { return false; }

	return true;
}

//破棄関数.
void CGame::Destroy()
{
	SAFE_DELETE( m_pCamera );

	SAFE_DELETE( m_pStage );

	SAFE_DELETE( m_pEnemy );

	SAFE_DELETE(m_ppshot);

	SAFE_DELETE( m_pPlayer );

	//BITMAPの解放.
	SAFE_DELETE( m_pStageImg );
	SAFE_DELETE(m_pRankImg);
	SAFE_DELETE( m_pPlayerImg);
	SAFE_DELETE(m_pPLeftImg);
	SAFE_DELETE( m_pBShotImg );
	SAFE_DELETE( m_pPShotImg );
	SAFE_DELETE(m_pSPMoveImg );
	SAFE_DELETE(m_pSPImg     );
	SAFE_DELETE(m_pSPGeagImg);
	SAFE_DELETE( m_pEnemyImg );
	SAFE_DELETE( m_pCharaImg );
	SAFE_DELETE(m_pSentakuImg);
	SAFE_DELETE( m_pBackImg  );

	SAFE_DELETE(m_pbossImg);
	SAFE_DELETE(m_pbossHandImg);
	SAFE_DELETE(m_pbossWayshotImg);


	SAFE_DELETE(m_pscoreImg);
	SAFE_DELETE(m_pExprotionImg);
	SAFE_DELETE(m_pEExprotionImg);

	//フォントの解放.
	DeleteObject( m_hFont );

	//作業用BITMAPの解放.
	DeleteObject( m_hWorkBmp );
	//作業用DCの解放.
	DeleteDC( m_hWorkDC );

	//メモリDCの解放.
	DeleteDC( m_hMemDC );
}

//更新関数(キー入力や動作処理を行う).
void CGame::Update()
{
	//BGM_Bonusをループ再生.
	if (m_scene == enScene::GameMain&& m_Exc->GetIAI() == false) {
		CSoundManager::PlayLoop(CSoundManager::enList::BGM_Bonus);
	}
	if (m_Exc->GetIAI() == true)
	{
		CSoundManager::Stop(CSoundManager::enList::BGM_Bonus);
	}

	if (m_scene == enScene::GameOver) {
		CSoundManager::Stop(CSoundManager::enList::BGM_Bonus);
		CSoundManager::PlayLoop(CSoundManager::enList::BGM_GameOver);
	}

	if (m_scene == enScene::Ending) {
		CSoundManager::Stop(CSoundManager::enList::BGM_Bonus);
		CSoundManager::PlayLoop(CSoundManager::enList::BGM_Ending);
	}

	switch (m_scene)
	{
		case enScene::Title:
		{
			if (GetAsyncKeyState(VK_RETURN) & 0x8000)
			{
				m_scene = enScene::GameMain;
			}
		}


		//ゲームメイン
		case enScene::GameMain:
		{

			if (GetAsyncKeyState('A') & 0x0001) {
				m_pBoss->B_HP = 100;

			}


			//F1キー.
			if (GetAsyncKeyState(VK_F1) & 0x0001) {
				//ウィンドウを閉じる通知を送る.
				PostMessage(m_pGameWnd->hWnd, WM_CLOSE, 0, 0);
			}

			//プレイヤー動作.
			m_pPlayer->Update();
			//プレイヤーショット
			m_ppshot->UpdateShot();

			m_Exc->UpdateKen();

			VECTOR2 playerPos = m_pPlayer->GetPosition();
			m_pEnemy->playerX = playerPos.x;
			m_pEnemy->playerY = playerPos.y;

			//エネミー動作.
			m_pEnemy->Update();

			//エネミー動作.
			m_pEnemy2->Update();

			//ステージ動作.
			m_pStage->Update();

			//ボス動作.
			m_pBoss->Update();

			//カメラ位置をプレイヤーに揃える.
			m_pCamera->SetPosition(m_pPlayer->GetPosition());



			for (int i = 0; i <= 50; i++) {


				//------------------------------
				// 剣と敵の当たり判定
				//----------------------------
				if (m_pEnemy->GetEnemyStetus()[i] == enCharaState::Living)
				{
					if (m_Hantei->collisionDetection(m_Exc->GetKenPosition().x, m_Exc->GetKenPosition().y, 100, 100,
						m_pEnemy->GetEPosition()[i].x, m_pEnemy->GetEPosition()[i].y, 32, 32)) {

						m_pEnemy->HIT(i);
						if (m_Exc->GetIAI() == true)
						{
							m_pEnemy2->HIT2(i);
							m_pEnemy2->ESHIT(i);
							m_pEnemy->HIT2(i);
							m_pEnemy->ESHIT(i);
							m_Exc->SPHIT();
						}
						/*m_scene = enScene::Ending;*/

					}




					//------------------------------
					// 敵とボムの当たり判定
					//----------------------------

					if (m_Hantei->collisionSpher(m_ppshot->GetBsPosition().x, m_ppshot->GetBsPosition().y, 64, 64,
						m_pEnemy->GetEPosition()[i].x, m_pEnemy->GetEPosition()[i].y, 32, 32)) {

						m_pEnemy->HIT(i);

					}


					//------------------------------
					// 敵と自機の当たり判定
					//----------------------------

					if (m_Hantei->collisionDetection(m_pPlayer->GetPosition().x, m_pPlayer->GetPosition().y, 64, 64,
						m_pEnemy->GetEPosition()[i].x, m_pEnemy->GetEPosition()[i].y, 32, 32)) {


						m_pPlayer->HIT();
						if (m_Exc->GetIAI() == true)
						{
							m_pEnemy2->HIT2(i);
							m_pEnemy2->ESHIT(i);
							m_pEnemy->HIT2(i);
							m_pEnemy->ESHIT(i);
							m_Exc->SPHIT();
						}

					}


					
				}

				if (m_pEnemy2->GetEnemyStetus2()[i] == enCharaState::Living)
				{
					//------------------------------
					// 敵と自機の当たり判定2
					//----------------------------

					if (m_Hantei->collisionDetection(m_pPlayer->GetPosition().x, m_pPlayer->GetPosition().y, 64, 64,
						m_pEnemy2->GetEPosition2().x, m_pEnemy2->GetEPosition2().y, 32, 32)) {


						m_pPlayer->HIT();
						if (m_Exc->GetIAI() == true)
						{
							m_pEnemy2->HIT2(i);
							m_pEnemy2->ESHIT(i);
							m_pEnemy->HIT2(i);
							m_pEnemy->ESHIT(i);
							m_Exc->SPHIT();
						}
						/*m_scene = enScene::Ending;*/

					}
					//------------------------------
					// 敵とボムの当たり判定2
					//----------------------------

					if (m_Hantei->collisionDetection(m_ppshot->GetBsPosition().x, m_ppshot->GetBsPosition().y, 64, 64,
						m_pEnemy2->GetEPosition2().x, m_pEnemy2->GetEPosition2().y, 32, 32)) {


						m_pEnemy2->HIT(i);
						/*m_scene = enScene::Ending;*/
					}
				}
					//------------------------------
					// 自機と敵の弾の当たり判定
					//----------------------------
				
					if (m_Hantei->collisionDetection(m_pPlayer->GetPosition().x, m_pPlayer->GetPosition().y, 64, 64,
						m_pEnemy->GetbulletPos().x, m_pEnemy->GetbulletPos().y, 32, 32)) {

						if (m_Exc->GetIAI() == true)
						{
							m_pEnemy2->HIT2(i);
							m_pEnemy2->ESHIT(i);
							m_pEnemy->HIT2(i);
							m_pEnemy->ESHIT(i);
							m_Exc->SPHIT();
						}
						m_pPlayer->HIT();
						/*m_scene = enScene::Ending;*/

					}


				//------------------------------
				// 反射弾と敵の弾の当たり判定
				//----------------------------
				
					//{
					//	if (m_Hantei->collisionDetection(m_ppshot->GetBsPosition().x, m_ppshot->GetBsPosition().y, 64, 64,
					//		m_pEnemy->GetbulletPos().x, m_pEnemy->GetbulletPos().y, 32, 32)) {
					//		m_pEnemy->ESHIT(i);
					//		/*m_scene = enScene::Ending;*/

					//	}
					//}
			}
			

			
			if (m_pBoss->m_BossState == m_pBoss->enBossState::Leving)
			{

				////ボスと剣の当たり判定
				//if (m_Hantei->collisionDetection(m_Exc->GetKenPosition().x, m_Exc->GetKenPosition().y, 100, 100,
				//	m_pBoss->BossGetPosition()->x, m_pBoss->BossGetPosition()->y, 356, 356)) {

				//	
				//	if (m_Exc->GetIAI() == true)
				//	{


				//		m_Exc->SPHIT();
				//	}
				//}
			}



			


			for (int i = 0; i <= 50; i++) {


				if (m_pPlayer->GetPlayerStetus() == enCharaState::Dead)
				{

					m_scene = enScene::GameOver;
				}

				//ゲームクリア条件仮
				if (m_pEnemy->GetEnemyStetus()[i] == enCharaState::Dead)
				{

					//m_scene = enScene::Ending;
				}

			}
	
		}

		case enScene::GameOver:
		{
			
			if (GetAsyncKeyState(VK_RETURN) & 0x8000) {
				m_scene = enScene::Result;
			}
		}

		case enScene::Ending:
		{
			if (GetAsyncKeyState(VK_RETURN) & 0x8000) {
				m_scene = enScene::Result;
			}
			m_Ending->Update();
		}

		case enScene::Result:
		{
			m_result->Update();
			
		}
	}
}

//描画関数(画像の表示処理を行う).
void CGame::Draw()
{

	if (m_scene == enScene::Title)
	{
		m_pTitle->XDraw(m_pCamera);
		m_pTitle->Draw(m_pCamera);
		m_pTitle->RDraw(m_pCamera);
	}

	if (m_scene==enScene::GameMain) {
		//ステージ描画.
		m_pStage->Draw(m_pCamera);

		m_pEnemy->Draw(m_pCamera);

		m_pEnemy2->Draw(m_pCamera);

		//ショット画像
		m_ppshot->DrawShot(m_pCamera);
		//プレイヤー描画.
		m_pPlayer->Draw(m_pCamera);
		//bomショット画像
		m_ppshot->DrawBomShot(m_pCamera);

		m_ppshot->DrawBomset(m_pCamera);

		m_Exc->DrawShotKen(m_pCamera);



		//ボス本体の描画
		m_pBoss->ZDraw(m_pCamera);

		//ボスの一部と攻撃を描画
		m_pBoss->Draw(m_pCamera);

		m_pBoss->XDraw(m_pCamera);

		m_pBoss->RDraw(m_pCamera);

	

		//必殺ショット画像
		m_ppshot->DrawSpecialmove(m_pCamera);

		//ゲージ画像
		m_Exc->DrawGeag(m_pCamera);
	}

	if (m_scene == enScene::Ending) {
		m_Ending->Draw(m_pCamera);
	}

	if (m_scene == enScene::GameOver) {
		m_GameOver->Draw(m_pCamera);
	}

	if (m_scene == enScene::Result) {
		m_result->Draw(m_pCamera);
	}
	
/*	SelectObject(m_hMemDC, m_pEnemyImg->GetBmp());
    //スクリーン→作業用DCへ.
    BitBlt(
        m_hWorkDC,              //出力先：作業用DC.
        0, 0,
        32, 32,
        m_pGameWnd->hScreenDC,  //読込元：スクリーン.
        x,
        y,
        SRCCOPY );
    //メモリ→作業用DCへ.
    TransparentBlt(
        m_hWorkDC,              //出力先：作業用DC.
        0, 0,
        32, 32,
        m_hMemDC,               //読込元：メモリ.
        32 * 6,
        0,
        32, 32,
        RGB( 0x00, 0xFF, 0x00 ) );
    //作業用DC→スクリーンへ.
    BLENDFUNCTION blendfunc = { AC_SRC_OVER, 0, 127,0 };
    AlphaBlend(
        m_pGameWnd->hScreenDC,  //出力先：スクリーン.
        x, y,
        32, 32,
        m_hWorkDC,              //読込元：作業用DC.
        0, 0,
        32, 32,
        blendfunc );
*/
}




//矩形同士の当たり判定.
bool CollisionDetection(
	int Ax, int Ay, int Aw, int Ah,	//矩形Aのx,y座標と幅高さ.
	int Bx, int By, int Bw, int Bh)	//矩形Bのx,y座標と幅高さ.
{
	//自機の弾と敵機の当たり判定.
	if( ( Ax <= Bx + Bw ) && ( Bx <= Ax + Aw ) &&
		( Ay <= By + Bh ) && ( By <= Ay + Ah ) )
	{
		//命中した時.
		return true;
	}
	//外れた時.
	return false;
}
