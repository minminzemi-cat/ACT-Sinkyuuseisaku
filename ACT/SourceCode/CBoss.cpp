#include "CGame.h"
#include "CBoss.h"
#include<time.h>
#include <cmath>
#include <vector>
#include <chrono>
#include <algorithm>

//コンストラクタ

CBoss::CBoss()
    :x(300)
    ,y(100)
    ,m_BossHurase  (enBossHurase::mid)
    ,m_RightLeft(1)
    , m_SyutuTimer(0)
{
}
CBoss::CBoss(GameWindow* pGameWnd)
{
}
//デストラクタ
CBoss::~CBoss()
{
}



//初期化（リセット）
void CBoss::InitializeGame()
{
    m_Boss.x = 300;
    m_Boss.y = 100;

   
    m_BossPosition->x = 300;
    m_BossPosition->y = 100;
}



constexpr float PI = 3.14159265358979323846f;

// --- 自機を遅くするWay弾発射 ---
void CBoss::SlowWayShot(int slowway, float angleRangeRad, float speed)
{
    float baseAngle = PI / 2.0f; // ９０度（真sita）

    for (int i = 0; i < slowway; i++) {
        float t = (slowway == 1) ? 0.0f : (float)i / (slowway - 1); // 0〜1
        float angle = baseAngle - angleRangeRad / 2.0f + angleRangeRad * t;

        CBoss::SlowWay b;
        b.qx = m_Boss.x  + (356 / 2);            //座標 356/2はボスの中心座標を求めている
        b.qy = m_Boss.y + (356 / 2)+100;
        b.vx = cosf(angle) * speed; //スピード  
        b.vy = sinf(angle) * speed;

        SlowWayShots.push_back(b);
    }
}


// --- Way弾発射 ---
void CBoss::Way(int way, float angleRangeRad, float speed) {
    float baseAngle = PI / 2.0f; // ９０度（真sita）

    for (int i = 0; i < way; i++) {
        float t = (way == 1) ? 0.0f : (float)i / (way - 1); // 0〜1
        float angle = baseAngle - angleRangeRad / 2.0f + angleRangeRad * t;

        CBoss::WayShot b;
        b.wx = m_Boss.x*2+90;            //座標
        b.wy = m_Boss.y*2+280;
        b.vx = cosf(angle) * speed; //スピード  
        b.vy = sinf(angle) * speed;

        WayShots.push_back(b);
    }
}


// --- バラマキ弾発射 ---
void CBoss::bara(int num, float speed) {
    for (int i = 0; i < num; i++) {
        float angle = 2.0f * PI * i / num; // 0〜360度に均等配置

        CBoss::Baramaki b;
        b.zx = m_Boss.x*2 +90;
        b.zy = m_Boss.y*2+30;
        b.vx = cosf(angle) * speed;
        b.vy = sinf(angle) * speed;

        BaraShots.push_back(b);
    }
}


// Δt計算
float dt = 1000 / FPS / 2 / 2; // 秒


// Δt計算
float dr = 1000 / FPS /2/2 ; // 秒

//自機を遅くするway
void CBoss::SlowUpdate() {
   

    // 遅くなれWay描画 ---
    fireTimer += dr;
    if (fireTimer >= fireInterval) {
        fireTimer = 10;
        SlowWayShot(3,30*PI/180,1);
        //3が3way弾ということを指している
        //30*PI/180が角度　　PIがπ
        //70が速度
    }
   

    // 弾の更新
    for (auto& b : SlowWayShots) {
        b.qx += b.vx; // 秒単位の移動
        b.qy += b.vy;
    }

    //// 画面外の弾を削除（-1.2〜1.2 の範囲外なら削除）
    SlowWayShots.erase(std::remove_if(SlowWayShots.begin(), SlowWayShots.end(),
        [](const CBoss::SlowWay& b) {
            return (b.qx < 0 || b.qx > 480 || b.qy < 0 || b.qy > 640);
       }), SlowWayShots.end());

}




//普通のway
void CBoss::WayUpdate()
{
    // --- Way描画 ---
    fireTimer += dt;
    if (fireTimer >= fireInterval) {
        fireTimer = 10;
        Way(3, 30 * PI / 180, 1);
        //3が3way弾ということを指している
        //30*PI/180が角度　　PIがπ
        //70が速度
    }


    // 弾の更新
    for (auto& b : WayShots) {
        b.wx += b.vx; // 秒単位の移動
        b.wy += b.vy;
    }

    //// 画面外の弾を削除（-1.2〜1.2 の範囲外なら削除）
    WayShots.erase(std::remove_if(WayShots.begin(), WayShots.end(),
        [](const CBoss::WayShot& b) {
            return (b.wx < 0 || b.wx > 480 || b.wy < 0 || b.wy > 640);
        }), WayShots.end());


}


//ボスの一部から発射される、ばらまき描画
void CBoss::BaraUpdate()
{
    // バラマキ弾発射
    BarafireTimer += dt;
    if (BarafireTimer >= BarafireInterval) {
        BarafireTimer = 100.0f;
        bara(9, 10);
    }


    // 弾の更新
    for (auto& b : BaraShots) {
        b.zx += b.vx;
        b.zy += b.vy;
    }

    // 画面外の弾を削除
    BaraShots.erase(std::remove_if(BaraShots.begin(), BaraShots.end(),
        [](const CBoss::Baramaki& b) {
            return (b.zx < 0 || b.zx > 480 || b.zy < 0 || b.zy > 640);
        }), BaraShots.end());
}
 


//-----------描画--------------------

void CBoss::Draw(CCamera*  pCamera)
{
    if(m_BossState==enBossState::Leving)
    { 
    
    //way弾の描画
    for (int i = 0; i < WayShots.size(); i++) {
        m_FrameSplit.w = 32;
        m_FrameSplit.h = 32;
        m_FrameSplit.x = 0;
        m_FrameSplit.y = 0;

        VECTOR2 shotpos;
        shotpos.x = WayShots[i].wx;
        shotpos.y = WayShots[i].wy;


        VECTOR2 DispPos5 = pCamera->CalcToPositionInCamera(&shotpos, &m_FrameSplit);

        m_pbossWayshotImg->TransBlt(
            DispPos5.x,
            DispPos5.y,
            m_FrameSplit.w,
            m_FrameSplit.h,
            m_FrameSplit.x,
            m_FrameSplit.y);

        }

    //スローway弾の描画
    for (int i = 0; i < SlowWayShots.size(); i++) {
        m_FrameSplit.w = 32;
        m_FrameSplit.h = 32;
        m_FrameSplit.x = 0;
        m_FrameSplit.y = 0;

        VECTOR2 shotpos;
        shotpos.x = SlowWayShots[i].qx;
        shotpos.y = SlowWayShots[i].qy;


        VECTOR2 DispPos6 = pCamera->CalcToPositionInCamera(&shotpos, &m_FrameSplit);

        m_pbossSlowshotImg->TransBlt(
            DispPos6.x,
            DispPos6.y,
            m_FrameSplit.w,
            m_FrameSplit.h,
            m_FrameSplit.x,
            m_FrameSplit.y);
        }

    
    

    //*****************************************************************:
    // **********************************************************************
    // 
    // 
    //ボスの体力が３０％以下のとき
    //
    //
    //*********************************************************************
    //***************************************************************************
    //if (B_HP <= 1000 * 0.3)
    //{


    //    //ボスの降らせ攻撃の状態による処理
    //    switch (m_BossHurase)
    //    {
    //    case enBossHurase::mid:   //待機

    //       
    //        break;

    //        //ｙ座標が下に移動する処理
    //    case enBossHurase::hurase:  //降らせる

    //      

    //        break;



    //        //ばらまき弾打つ
    //    case enBossHurase::utima:       //弾を打つ  


            //ばらまき弾の描画
            for (int i = 0; i < BaraShots.size(); i++) {
                m_FrameSplit.w = 32;
                m_FrameSplit.h = 32;
                m_FrameSplit.x = 0;
                m_FrameSplit.y = 0;

                VECTOR2 shotpos;
                shotpos.x = BaraShots[i].zx;
                shotpos.y = BaraShots[i].zy;


                VECTOR2 DispPos4 = pCamera->CalcToPositionInCamera(&shotpos, &m_FrameSplit);

                m_pbossbuiImg->TransBlt(
                    DispPos4.x,
                    DispPos4.y,
                    m_FrameSplit.w,
                    m_FrameSplit.h,
                    m_FrameSplit.x,
                    m_FrameSplit.y);

            }

    //        break;

    //        //元に戻ってくる
    //    case enBossHurase::modorima:

    //        XDraw(pCamera);
    //        RDraw(pCamera);

    //        //ボスの一部が空中で止めた座標より下だった場合
    //        //
    //        while (m_Boss_BuiPosition->y >= 500)
    //        {
    //            m_Boss_BuiPosition->y -= 2;
    //        }


    //        break;
    //    }
    //  }
    }
    
    if (m_BossState == enBossState::Explsion)
    {
        //爆発アニメーション
        ExplosionAnimation();
    }

    if (m_BossState == enBossState::Ded)
    {
        //何もしない
    }
}


//ボス本体の描画  
void CBoss::ZDraw(CCamera* pCamera)
{
    //ボス本体の描画

    if (m_BossState != enBossState::Leving) {
        return;
    }

    m_FrameSplit.w = 356;
    m_FrameSplit.h = 356;
    m_FrameSplit.x = 0;
    m_FrameSplit.y = 0;

    m_bossIMG->TransBlt(
        m_Boss.x,
        m_Boss.y,
        m_FrameSplit.w,
        m_FrameSplit.h,
        m_FrameSplit.x,
        m_FrameSplit.y);

   
}

void CBoss::XDraw(CCamera* pCamera)
{
    if (m_BossState != enBossState::Leving) {
        return;
    }

    //ボスの一部を描画する
    m_FrameSplit.w = 113;
    m_FrameSplit.h = 94;
    m_FrameSplit.x = 0;
    m_FrameSplit.y = 0;


    //いい位置になるよう調整
    m_Boss_bui.x = m_Boss.x + 170;
    m_Boss_bui.y = m_Boss.y + 70;

   
    m_pbossHandImg->TransBlt(
        m_Boss_bui.x,
        m_Boss_bui.y,
        m_FrameSplit.w,
        m_FrameSplit.h,
        m_FrameSplit.x,
        m_FrameSplit.y);

}

void CBoss::RDraw(CCamera* pCamera)
{
    if (m_BossState != enBossState::Leving) {
        return;
    }

    //ボスの一部を描画する
    m_FrameSplit.w = 113;
    m_FrameSplit.h = 94;
    m_FrameSplit.x = 0;
    m_FrameSplit.y = 0;

   
    m_Boss_bui.x = m_Boss.x + 70;
    m_Boss_bui.y = m_Boss.y + 70;


    m_pbossHandImg->TransBlt(
        m_Boss_bui. x,
        m_Boss_bui.y,
        m_FrameSplit.w,
        m_FrameSplit.h,
        m_FrameSplit.x,
        m_FrameSplit.y);

}


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// 
// 
//動作処理   UPDATE
// 
// 
//+++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


void CBoss::Update()
{
    //秒ごとに処理ができるようにするための変数
    //谷口君に教えてもらった
    int time=0;
    time++;
    //体力が３０％以上のときは左右に動くことを続ける
    if (B_HP >= 1000 * 0.3)
    {
    if (m_BossState == enBossState::Wait) {
        m_SyutuTimer += (1.0f / 60.0f);//これは一秒の計算

        if (m_SyutuTimer >= syutugentime) {
            m_BossState = enBossState::Leving; // 10秒経ったら登場
        }
        return; 
    }

    //ボスが生きているとき
    if (m_BossState == enBossState::Leving)
    {

        //左右に動くようにする

        //何秒ごとに

        //ボスがボススピードで左右に動き
        //画面端に行ったら反対方向にボススピードで動く


            //メンバー変数を使うことで値の保持が可能
        if (m_Boss.x >= 270)
        {
            m_RightLeft = -1.f;
        }

        //左に行く
        if (m_Boss.x <= -100)
        {
            m_RightLeft = 1.f;
        }

        //最初は右に動く
        m_Boss.x += m_RightLeft * B_SPD;

        shotpos.x = m_Boss.x;
        shotpos.y = m_Boss.y;

        //
        /*m_BossPosition->x =m_Boss.x;
        m_BossPosition->y = m_Boss.y;*/

        bosstime++;



        //ボスの体力が30％以上のとき、一分間このような処理を繰り返す
        if (bosstime > 6000 )
        {
            bosstime = 0;
        }

        if (bosstime < 3000 / 60)
        {

        }

        if (bosstime < 6000 / 60)
        {
        }

        CBoss::WayUpdate();
        CBoss::SlowUpdate();



        //CBoss::Way(4, 15, 1);



    ///////////////////////////////////////////////////////////////
    // //////////////////////////////////////////////////////
    // 
    //ボスの体力が30％以下になったら************
    //
    //
    ////////////////////////////////////////////////////////////

        if (B_HP <= 1000 * 0.3)

        {
            //ボスの降らせ攻撃の状態による処理
            switch (m_BossHurase)
            {
                //ボス本体を中央に移動させる
            case enBossHurase::mid:

                if (m_Boss.x < 240) {
                    m_Boss.x += 1.0f;
                }

                else {
                    if (m_Boss.x > 240)
                        m_Boss.x -= 1.0f;
                }

                // 中央にきたら
                if (m_Boss.x <= 2.0f) {
                    m_Boss.x = 240;
                    m_BossHurase = enBossHurase::hurase;
                }
                break;

                //時間で処理をする　
                //1秒ごとに次の状態へ
            case enBossHurase::hurase:
                m_Boss_BuiPosition->y += 2.0f;
                if (m_Boss_BuiPosition->y >= 400.0f) {
                    m_BossHurase = enBossHurase::utima;
                }

                break;



                //ばらまき弾打つ
            case enBossHurase::utima:

                CBoss::BaraUpdate();

                m_BossHurase = enBossHurase::modorima;


                break;

                //元に戻ってくる
            case enBossHurase::modorima:


                m_BossHurase = enBossHurase::utima;


                break;
            }

        }
    }
    }
}
//爆発アニメーション関数
void  CBoss::ExplosionAnimation()
{

    //画像のサイズを間違えると描画されない
    //ディエゴのおかげ
    m_FrameSplit.w = 192;
    m_FrameSplit.h = 192;
    m_FrameSplit.y = 0;
    //僕の画像はこの大きさでないとだめ

    m_pbossBomImg->TransBlt(
        m_Boss.x,
        m_Boss.y,
        m_FrameSplit.w,
        m_FrameSplit.h,
        m_FrameSplit.x,
        m_FrameSplit.y);



        //爆発の描画
    if (m_FrameCounter >= 11) {

        //　　　0       +=     192
        m_FrameSplit.x += m_FrameSplit.w;

        m_FrameCounter = 1;

    }

}
