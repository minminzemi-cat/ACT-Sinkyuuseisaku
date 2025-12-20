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
    ,m_BossHurase  (enBossHurase::taiki)
    ,m_RightLeft(1)
{
}
CBoss::CBoss(GameWindow* pGameWnd)
{
}
//デストラクタ
CBoss::~CBoss()
{
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
        b.qx = m_Boss.x * 2 + 90;            //座標
        b.qy = m_Boss.y * 2 + 280;
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

//初期化（リセット）
void CBoss::InitializeGame()
{
    m_Boss.x = 60;
    m_Boss.y = 30;

}


// Δt計算
float dt = 1000 / FPS / 2 / 2; // 秒


//自機を遅くするway
void CBoss::SlowDraw(CCamera* pCamera) {
   

    // 遅くなれWay描画 ---
    fireTimer += dt;
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
void CBoss::WayDraw(CCamera* pCamera)
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
void CBoss::BaraDraw(CCamera* pCamera)
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
 

//---------ボスの一部描画--------------------

void CBoss::Draw(CCamera*  pCamera)
{

    
    

    //ボスの降らせ攻撃の状態による処理
    switch (m_BossHurase)
    {
    case enBossHurase::taiki:   //待機


    //この｛はcaseラベルのせいでDispPosが初期化されないらしいから入れた
    {
        //ボスの一部を描画する
        m_FrameSplit.w = 113;
        m_FrameSplit.h = 94;
        m_FrameSplit.x = 0;
        m_FrameSplit.y = 0;

        m_Boss_BuiPosition->x = m_Boss.x + 70;
        m_Boss_BuiPosition->y = m_Boss.y;
        VECTOR2 DispPos1 = pCamera->CalcToPositionInCamera(m_Boss_BuiPosition, &m_FrameSplit);

        m_bossIMG->TransBlt(
            DispPos1.x,
            DispPos1.y,
            m_FrameSplit.w,
            m_FrameSplit.h,
            m_FrameSplit.x,
            m_FrameSplit.y);



        m_Boss_BuiPosition->x = m_Boss.x + 170;
        m_Boss_BuiPosition->y = m_Boss.y;
        VECTOR2 DispPos2 = pCamera->CalcToPositionInCamera(m_Boss_BuiPosition, &m_FrameSplit);

        m_bossIMG->TransBlt(
            DispPos2.x,
            DispPos2.y,
            m_FrameSplit.w,
            m_FrameSplit.h,
            m_FrameSplit.x,
            m_FrameSplit.y);


        break;
    }



    //ｙ座標が下に移動する処理
    case enBossHurase::hurase:  //降らせる
   
        m_Boss_BuiPosition->y += 2;

        break;

        //空中で止める
    case enBossHurase::tome:        //空中で止める
        if (m_Boss_BuiPosition->y >= 500)
        {
            m_Boss_BuiPosition->y == 500;
        }
        break;

        //ばらまき弾打つ
    case enBossHurase::utima:       //弾を打つ  
        
        //ばらまき描画
        CBoss::BaraDraw(pCamera);

        break;

        //元に戻ってくる
    case enBossHurase::modorima:

        //ボスの一部が空中で止めた座標より下だった場合
        //
        while (m_Boss_BuiPosition->y >= 500)
        {
            m_Boss_BuiPosition->y -= 2;
        }
       

        break;
    }

}

//ボス本体の描画  
void CBoss::ZDraw(HDC m_hMemDC)
{
    //ボス本体の描画

    m_FrameSplit.w = 356;
    m_FrameSplit.h = 356;
    m_FrameSplit.x = 0;
    m_FrameSplit.y = 0;

    m_bossIMG->TransBlt(
        m_BossPosition->x,
        m_BossPosition->y,
        m_FrameSplit.w,
        m_FrameSplit.h,
        m_FrameSplit.x,
        m_FrameSplit.y);


}



//-----------------------------------
//動作処理
//-------------------------------------
void CBoss::Update()
{
    //秒ごとに処理ができるようにするための変数
    //谷口君に教えてもらった
    int aaaaa=0;
    aaaaa++;

    //左右に動くようにする

    //何秒ごとに

    //ボスがボススピードで左右に動き
    //画面端に行ったら反対方向にボススピードで動く

    //体力が３０％以上のときは左右に動くことを続ける
    if(B_HP >= B_HP * 0.3)
    {
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

    }


    //ボスの体力が30％以下になったら************
    
    if (B_HP <= B_HP * 0.3)

    {
        //ボスの降らせ攻撃の状態による処理
        switch (m_BossHurase)
        {

            //時間で処理をする　
            //1秒ごとに次の状態へ
        case enBossHurase::hurase:

            if (aaaaa / 60 == 0) {
                m_BossHurase = enBossHurase::tome;
            }

            break;

            //空中で止める
        case enBossHurase::tome:
            if (aaaaa / 60 == 0) {

                m_BossHurase = enBossHurase::utima;
            }

            break;

            //ばらまき弾打つ
        case enBossHurase::utima:
            if (aaaaa / 60 == 0) {

                m_BossHurase = enBossHurase::modorima;
            }

            break;

            //元に戻ってくる
        case enBossHurase::modorima:
            if (aaaaa / 60 == 0) {

                m_BossHurase = enBossHurase::hurase;

            }
            break;
        }

    }
}

