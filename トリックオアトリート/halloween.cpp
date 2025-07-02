//////////////////////////////////////////////////////////////////////
//
// 夏休み課題　j2038 山根和佳.cpp
//　　
//　　DXライブラリ使用
// 
//　松江工業高等専門学校　情報工学科　j2038　山根和佳
//							令和3年9月10日
//  素材配布元
//  背景やおばけの画像：イラストAC https://www.ac-illust.com/
//　ドアや人物の画像： いらすとや https://www.irasutoya.com/
//  bgm： フリー音楽素材サイト「PeriTune」　https://peritune.com/
//  ノックの音：電脳プロダクション　https://www.d-pro.tokyo/se5
//////////////////////////////////////////////////////////////////////
#include "DxLib.h"

//お菓子の数を表示
void Drawtreat(int Cr,int cHandle,int cr,static int treat)
{
    DrawBox(450, 0, 640, 30, Cr, TRUE);
    DrawModiGraph(460, -5, 510, -5, 510, 40, 460, 40, cHandle, TRUE);
    DrawFormatString(450, 0, cr, "　　：%d", treat);
}

//ドアを開ける表示
void OpenDoor(int HHandle,int DHandle)
{
    // 読みこんだグラフィックを自由変形描画
    DrawModiGraph(170, 100, 435, 100, 435, 560, 170, 560, HHandle, TRUE);
    WaitTimer(300);// ここで0.3秒待つ
    DrawModiGraph(5, 100, 430, 100, 430, 560, 5, 560, DHandle, TRUE);
    WaitTimer(300);
}

//ゲームオーバー
void gameover(int ktHandle,int Cr)
{
    SetFontSize(50);//文字の大きさを変える
    DrawGraph(0, 0, ktHandle, TRUE);
    DrawFormatString(200, 400, Cr, "GAME OVER");
    WaitTimer(2000);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    int GHandle,WHandle,CHandle,HHandle,DHandle,THandle,gHandle,dHandle,ktHandle,gtHandle,H2Handle,cHandle,PHandle,AHandle,clHandle;
    int SHandle,N9Handle,N8Handle,N7Handle;
    int ra;
    int give;//あげたお菓子の数
    unsigned int Cr,cr,bc,pa;
    static int back = 0;
    static int treat;//お菓子の数

    // 橙の色コードを保存
    cr = GetColor(255, 130, 0);
    // 白の色コードを保存
    Cr = GetColor(255, 255, 255);
    // 黒の色コードを保存
    bc= GetColor(0, 0, 0);
    // 紫の色コードを保存
    pa= GetColor(255, 0, 255);

    if (DxLib_Init() == -1)// ＤＸライブラリ初期化処理
    {
        return -1;         // エラーが起きたら直ちに終了
    }

    // ウインドウモードに変更
    ChangeWindowMode(TRUE);

    //音楽ファイルをメモリへ読み込み、サウンドハンドルを保存
    SHandle = LoadSoundMem("PerituneMaterial_Spook2.mp3");//bgm
    N9Handle= LoadSoundMem("nock9.mp3");    //
    N8Handle = LoadSoundMem("nock8.mp3");   //ノックの音
    N7Handle = LoadSoundMem("nock7.mp3");   //

    // 画像ファイルをメモリへ読みこみ、グラフィックハンドルを保存
    //GHandle = LoadGraph("haikei.png");//タイトル画面
    WHandle = LoadGraph("wall.png");//煉瓦の壁
    CHandle = LoadGraph("close.png");//閉まったドア
    HHandle = LoadGraph("half.png");//少し開いたドア
    DHandle = LoadGraph("door.png");//開いたドア
    THandle = LoadGraph("tri.png");//三人の子供
    gHandle = LoadGraph("ghost.png");//おばけ
    dHandle = LoadGraph("dorobo.png");//強盗
    ktHandle= LoadGraph("ktrick.png");//子供のいたずら
    gtHandle = LoadGraph("gtrick.png");//おばけのいたずら
    H2Handle = LoadGraph("haikei2.jpg");//タイトル画面
    cHandle = LoadGraph("candy.png");//キャンディ
    PHandle = LoadGraph("pumpkin.png");//かぼちゃの仮装をした子供
    AHandle = LoadGraph("akuma.png");//悪魔の仮装をした子供
    clHandle = LoadGraph("clear.jpg");//クリア画面

    PlayMusic("PerituneMaterial_Spook2.mp3", DX_PLAYTYPE_LOOP); // 読みこんだ音をループ再生
    SetVolumeMusic(150);//音楽の大きさを変える
    DrawGraph(-20, 0, H2Handle, TRUE);    //読み込んだグラフィックを描画
    SetFontSize(25);

    while (1)
    {
        DrawFormatString(200, 400, Cr, "ENTERキーを押してください");
        if (CheckHitKey(KEY_INPUT_RETURN)== 1)//enterキーを押すまで待つ
            break;
    }

    StopSoundMem(SHandle);//BGMを止める
    // 読み込んだ画像のグラフィックハンドルを削除
   // DeleteGraph(GHandle);
   
    while(1)
    {
        treat = 80;
        give = 0;
        
        PlayMusic("PerituneMaterial_Spook2.mp3", DX_PLAYTYPE_LOOP);
        SetVolumeMusic(80);
        DrawGraph(0, 0, WHandle, TRUE);

        // 主なループで必ず呼ばないといけない関数
        // メッセージループに代わる処理をする
        if (ProcessMessage() == -1)
        {
              DxLib_End();	// ＤＸライブラリ使用の終了処理
              return 0;		// ソフトの終了
          
        }

        for (int i = 0; i < 20; i++)
        {
            ra = GetRand(100);//乱数を取得
            back = 0;
            DrawGraph(0, 0, WHandle, TRUE);
            DrawGraph(170, 100, CHandle, TRUE);
            Drawtreat(Cr,cHandle,cr,treat);
            WaitTimer(1000);
         
           //最初の三回以降は速くなる
           if(i<3)
               WaitTimer(2000);
           //十回目からはさらに速くなる
           else if (i < 10)
               WaitTimer(1000);

           //訪ねてくるものは乱数で決まる
           //強盗の場合
           if (ra<=10)
           {
               PlaySoundMem(N9Handle, DX_PLAYTYPE_BACK);
               for (int i = 0; i < 3000; i++)
               {
                   if (CheckHitKey(KEY_INPUT_RETURN) == 1)
                       break;
                   //バックスペースキーを押してから離すまで待つ
                   if (CheckHitKey(KEY_INPUT_BACK) == 1)
                   {
                       while (CheckHitKey(KEY_INPUT_BACK) == 1)
                       {
                           WaitTimer(1);
                       }
                       back++;
                   }
                   WaitTimer(1);
               }
               if (back < 8)//バックスペースキーを押した数が足りなかったら
               {
                   OpenDoor(HHandle, DHandle);
                   DrawModiGraph(100, 110, 500, 110, 500, 492, 100, 492, dHandle, TRUE);
                   treat -= 80;
                   Drawtreat(Cr, cHandle, cr, treat);
               }
           }
           //おばけの場合
           else if((ra>=11)&&(ra<=20))
           {
               PlaySoundMem(N7Handle, DX_PLAYTYPE_BACK);
               for (int i = 0; i < 2000; i++)
               {
                   if (CheckHitKey(KEY_INPUT_RETURN) == 1)
                       break;
                   if (CheckHitKey(KEY_INPUT_BACK) == 1)
                   {
                       back++;
                   }
                   WaitTimer(1);
               }
               if (CheckHitKey(KEY_INPUT_RETURN) == 1)
               {
                   OpenDoor(HHandle, DHandle);
                   DrawModiGraph(100, 100, 500, 100, 500, 490, 100, 490, gHandle, TRUE);
                   WaitTimer(1000);
                   DrawGraph(0, 0, gtHandle, TRUE);
                   gameover(gtHandle, Cr);
                   return 0;
               }
               if (back != 0)//バックスペースキーを押してしまったら
               {
                   DrawGraph(0, 0, gtHandle, TRUE);
                   WaitTimer(1000);
                   gameover(gtHandle, Cr);
                   return 0;
               }
           }
           //かぼちゃの仮装をした子供の場合
           else if ((21 <= ra) && (ra <= 30))
           {
               PlaySoundMem(N8Handle, DX_PLAYTYPE_BACK);
              // wait(back);
               for (int i = 0; i < 2000; i++)
               {
                   if (CheckHitKey(KEY_INPUT_RETURN) == 1)
                       break;
                   if (CheckHitKey(KEY_INPUT_BACK) == 1)
                   {
                       back++;
                   }
                   WaitTimer(1);
               }
               if (CheckHitKey(KEY_INPUT_RETURN) == 1)
               {
                   OpenDoor(HHandle, DHandle);
                   DrawModiGraph(150, 220, 400, 220, 400, 485, 150, 485, PHandle, TRUE);
                   treat -= 1;
                   give += 1;
                   Drawtreat(Cr, cHandle, cr, treat);
               }
               if (back != 0)//バックスペースキーを押してしまったら
               {
                   DrawGraph(0, 0, ktHandle, TRUE);
                   treat -= 30;
                   Drawtreat(Cr, cHandle, cr, treat);
               }
           }
           //悪魔の仮装をした子供の場合
           else if ((31 <= ra) && (ra <= 40))
           {
               PlaySoundMem(N8Handle, DX_PLAYTYPE_BACK);
               for (int i = 0; i < 2000; i++)
               {
                   if (CheckHitKey(KEY_INPUT_RETURN) == 1)
                       break;
                   if (CheckHitKey(KEY_INPUT_BACK) == 1)
                   {
                       back++;
                   }
                   WaitTimer(1);
               }
               if (CheckHitKey(KEY_INPUT_RETURN) == 1)
               {
                   OpenDoor(HHandle, DHandle);
                   DrawModiGraph(150, 220, 400, 220, 400, 485, 150, 485, AHandle, TRUE);
                   treat -= 1;
                   give += 1;
                   Drawtreat(Cr, cHandle, cr, treat);
               }
               if (back != 0)//バックスペースキーを押してしまったら
               {
                   DrawGraph(0, 0, ktHandle, TRUE);
                   treat -= 30;
                   Drawtreat(Cr, cHandle, cr, treat);
               }
           }
           //三人の子供の場合
           else
           {
               PlaySoundMem(N8Handle, DX_PLAYTYPE_BACK);
               for (int i = 0; i < 2000; i++)
               {
                   if (CheckHitKey(KEY_INPUT_RETURN) == 1)
                       break;
                   if (CheckHitKey(KEY_INPUT_BACK) == 1)
                   {
                       back++;
                   }
                   WaitTimer(1);
               }

               if (CheckHitKey(KEY_INPUT_RETURN) == 1)
               {
                   OpenDoor(HHandle,DHandle);
                   DrawModiGraph(150, 220, 600, 220, 600, 488, 150, 488, THandle, TRUE);
                   treat -= 3;
                   give += 3;
                   Drawtreat(Cr, cHandle, cr, treat);
               }
               if (back != 0)
               {
                   DrawGraph(0, 0, ktHandle, TRUE);
                   treat -= 30;
                   Drawtreat(Cr, cHandle, cr, treat);
                   WaitTimer(1000);
               }
           }
           if (treat < 0)
           {
               break;
           }
           if(i<=3)
               WaitTimer(2000);
           else //if(i<=10)
               WaitTimer(1000);
        }
        if (treat < 0)//お菓子が足りなくなったらゲームオーバー
            break;
        else if(treat<50)//ある程度お菓子がなくなったらゲームクリア
        {
            SetFontSize(50);
            DrawBox(0, 0, 640, 480, bc, TRUE);
            DrawGraph(0, 0, clHandle, TRUE);
            DrawBox(120, 80, 530, 200, pa, TRUE);
            DrawFormatString(200, 100, Cr, "GAME CLEAR");
            DrawFormatString(120, 150, Cr, "あげたお菓子：%d",give);
            WaitTimer(10000);
            DxLib_End();
            return 0;
        }
    }
    gameover(ktHandle,Cr);
    DxLib_End();        // ＤＸライブラリ使用の終了処理
    return 0;        // ソフトの終了
}