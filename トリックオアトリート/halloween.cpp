//////////////////////////////////////////////////////////////////////
//
// �ċx�݉ۑ�@j2038 �R���a��.cpp
//�@�@
//�@�@DX���C�u�����g�p
// 
//�@���]�H�ƍ������w�Z�@���H�w�ȁ@j2038�@�R���a��
//							�ߘa3�N9��10��
//  �f�ޔz�z��
//  �w�i�₨�΂��̉摜�F�C���X�gAC https://www.ac-illust.com/
//�@�h�A��l���̉摜�F ���炷�Ƃ� https://www.irasutoya.com/
//  bgm�F �t���[���y�f�ރT�C�g�uPeriTune�v�@https://peritune.com/
//  �m�b�N�̉��F�d�]�v���_�N�V�����@https://www.d-pro.tokyo/se5
//////////////////////////////////////////////////////////////////////
#include "DxLib.h"

//���َq�̐���\��
void Drawtreat(int Cr,int cHandle,int cr,static int treat)
{
    DrawBox(450, 0, 640, 30, Cr, TRUE);
    DrawModiGraph(460, -5, 510, -5, 510, 40, 460, 40, cHandle, TRUE);
    DrawFormatString(450, 0, cr, "�@�@�F%d", treat);
}

//�h�A���J����\��
void OpenDoor(int HHandle,int DHandle)
{
    // �ǂ݂��񂾃O���t�B�b�N�����R�ό`�`��
    DrawModiGraph(170, 100, 435, 100, 435, 560, 170, 560, HHandle, TRUE);
    WaitTimer(300);// ������0.3�b�҂�
    DrawModiGraph(5, 100, 430, 100, 430, 560, 5, 560, DHandle, TRUE);
    WaitTimer(300);
}

//�Q�[���I�[�o�[
void gameover(int ktHandle,int Cr)
{
    SetFontSize(50);//�����̑傫����ς���
    DrawGraph(0, 0, ktHandle, TRUE);
    DrawFormatString(200, 400, Cr, "GAME OVER");
    WaitTimer(2000);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    int GHandle,WHandle,CHandle,HHandle,DHandle,THandle,gHandle,dHandle,ktHandle,gtHandle,H2Handle,cHandle,PHandle,AHandle,clHandle;
    int SHandle,N9Handle,N8Handle,N7Handle;
    int ra;
    int give;//���������َq�̐�
    unsigned int Cr,cr,bc,pa;
    static int back = 0;
    static int treat;//���َq�̐�

    // ��̐F�R�[�h��ۑ�
    cr = GetColor(255, 130, 0);
    // ���̐F�R�[�h��ۑ�
    Cr = GetColor(255, 255, 255);
    // ���̐F�R�[�h��ۑ�
    bc= GetColor(0, 0, 0);
    // ���̐F�R�[�h��ۑ�
    pa= GetColor(255, 0, 255);

    if (DxLib_Init() == -1)// �c�w���C�u��������������
    {
        return -1;         // �G���[���N�����璼���ɏI��
    }

    // �E�C���h�E���[�h�ɕύX
    ChangeWindowMode(TRUE);

    //���y�t�@�C�����������֓ǂݍ��݁A�T�E���h�n���h����ۑ�
    SHandle = LoadSoundMem("PerituneMaterial_Spook2.mp3");//bgm
    N9Handle= LoadSoundMem("nock9.mp3");    //
    N8Handle = LoadSoundMem("nock8.mp3");   //�m�b�N�̉�
    N7Handle = LoadSoundMem("nock7.mp3");   //

    // �摜�t�@�C�����������֓ǂ݂��݁A�O���t�B�b�N�n���h����ۑ�
    //GHandle = LoadGraph("haikei.png");//�^�C�g�����
    WHandle = LoadGraph("wall.png");//�����̕�
    CHandle = LoadGraph("close.png");//�܂����h�A
    HHandle = LoadGraph("half.png");//�����J�����h�A
    DHandle = LoadGraph("door.png");//�J�����h�A
    THandle = LoadGraph("tri.png");//�O�l�̎q��
    gHandle = LoadGraph("ghost.png");//���΂�
    dHandle = LoadGraph("dorobo.png");//����
    ktHandle= LoadGraph("ktrick.png");//�q���̂�������
    gtHandle = LoadGraph("gtrick.png");//���΂��̂�������
    H2Handle = LoadGraph("haikei2.jpg");//�^�C�g�����
    cHandle = LoadGraph("candy.png");//�L�����f�B
    PHandle = LoadGraph("pumpkin.png");//���ڂ���̉����������q��
    AHandle = LoadGraph("akuma.png");//�����̉����������q��
    clHandle = LoadGraph("clear.jpg");//�N���A���

    PlayMusic("PerituneMaterial_Spook2.mp3", DX_PLAYTYPE_LOOP); // �ǂ݂��񂾉������[�v�Đ�
    SetVolumeMusic(150);//���y�̑傫����ς���
    DrawGraph(-20, 0, H2Handle, TRUE);    //�ǂݍ��񂾃O���t�B�b�N��`��
    SetFontSize(25);

    while (1)
    {
        DrawFormatString(200, 400, Cr, "ENTER�L�[�������Ă�������");
        if (CheckHitKey(KEY_INPUT_RETURN)== 1)//enter�L�[�������܂ő҂�
            break;
    }

    StopSoundMem(SHandle);//BGM���~�߂�
    // �ǂݍ��񂾉摜�̃O���t�B�b�N�n���h�����폜
   // DeleteGraph(GHandle);
   
    while(1)
    {
        treat = 80;
        give = 0;
        
        PlayMusic("PerituneMaterial_Spook2.mp3", DX_PLAYTYPE_LOOP);
        SetVolumeMusic(80);
        DrawGraph(0, 0, WHandle, TRUE);

        // ��ȃ��[�v�ŕK���Ă΂Ȃ��Ƃ����Ȃ��֐�
        // ���b�Z�[�W���[�v�ɑ��鏈��������
        if (ProcessMessage() == -1)
        {
              DxLib_End();	// �c�w���C�u�����g�p�̏I������
              return 0;		// �\�t�g�̏I��
          
        }

        for (int i = 0; i < 20; i++)
        {
            ra = GetRand(100);//�������擾
            back = 0;
            DrawGraph(0, 0, WHandle, TRUE);
            DrawGraph(170, 100, CHandle, TRUE);
            Drawtreat(Cr,cHandle,cr,treat);
            WaitTimer(1000);
         
           //�ŏ��̎O��ȍ~�͑����Ȃ�
           if(i<3)
               WaitTimer(2000);
           //�\��ڂ���͂���ɑ����Ȃ�
           else if (i < 10)
               WaitTimer(1000);

           //�K�˂Ă�����̂͗����Ō��܂�
           //�����̏ꍇ
           if (ra<=10)
           {
               PlaySoundMem(N9Handle, DX_PLAYTYPE_BACK);
               for (int i = 0; i < 3000; i++)
               {
                   if (CheckHitKey(KEY_INPUT_RETURN) == 1)
                       break;
                   //�o�b�N�X�y�[�X�L�[�������Ă��痣���܂ő҂�
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
               if (back < 8)//�o�b�N�X�y�[�X�L�[����������������Ȃ�������
               {
                   OpenDoor(HHandle, DHandle);
                   DrawModiGraph(100, 110, 500, 110, 500, 492, 100, 492, dHandle, TRUE);
                   treat -= 80;
                   Drawtreat(Cr, cHandle, cr, treat);
               }
           }
           //���΂��̏ꍇ
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
               if (back != 0)//�o�b�N�X�y�[�X�L�[�������Ă��܂�����
               {
                   DrawGraph(0, 0, gtHandle, TRUE);
                   WaitTimer(1000);
                   gameover(gtHandle, Cr);
                   return 0;
               }
           }
           //���ڂ���̉����������q���̏ꍇ
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
               if (back != 0)//�o�b�N�X�y�[�X�L�[�������Ă��܂�����
               {
                   DrawGraph(0, 0, ktHandle, TRUE);
                   treat -= 30;
                   Drawtreat(Cr, cHandle, cr, treat);
               }
           }
           //�����̉����������q���̏ꍇ
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
               if (back != 0)//�o�b�N�X�y�[�X�L�[�������Ă��܂�����
               {
                   DrawGraph(0, 0, ktHandle, TRUE);
                   treat -= 30;
                   Drawtreat(Cr, cHandle, cr, treat);
               }
           }
           //�O�l�̎q���̏ꍇ
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
        if (treat < 0)//���َq������Ȃ��Ȃ�����Q�[���I�[�o�[
            break;
        else if(treat<50)//������x���َq���Ȃ��Ȃ�����Q�[���N���A
        {
            SetFontSize(50);
            DrawBox(0, 0, 640, 480, bc, TRUE);
            DrawGraph(0, 0, clHandle, TRUE);
            DrawBox(120, 80, 530, 200, pa, TRUE);
            DrawFormatString(200, 100, Cr, "GAME CLEAR");
            DrawFormatString(120, 150, Cr, "���������َq�F%d",give);
            WaitTimer(10000);
            DxLib_End();
            return 0;
        }
    }
    gameover(ktHandle,Cr);
    DxLib_End();        // �c�w���C�u�����g�p�̏I������
    return 0;        // �\�t�g�̏I��
}