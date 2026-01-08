#include"CTimer.h"

CTimer::CTimer()
{
}

CTimer::~CTimer()
{
}


//ゲームメインで残り時間を表示
void CTimer::Draw(int x, int y, int times)
{


    //何もしないで終了する
    if (m_TimerImg == nullptr)
    {
        return;
    }

    

    // 残り時間を別の変数に
    
    int Target = kuriaTimer;

    // 今何桁目を描画しているか
    int digit = 0;

    
    do
    {
        //一番下の桁を取り出す
        
        int simoketa = Target % 10;

        //画像を描画する 
        m_TimerImg->TransBlt(
            x - 32 - 32 * digit,    //表示するx座標
            y,                      //表示するy座標
            32, 32,                 //幅、高さ
            32 * simoketa,          //取り出す元画像のx座標
            0                       //元画像y座標
        );

        //次の桁へ
        
        Target /= 10;

        digit++;

        //対象が0になるまで繰り返す
    } while (Target > 0);


}


void CTimer::Update(int times)
{
    ////タイムに秒数が追加されていく処理
    //int count = 0;
    //count++;
    //if (count % FPS == 0)
    //{
    //    times++;
    //}

    //残り時間　　クリアタイム　- 経過じた時間
    kuriaTimer = kuriatime - times;

}