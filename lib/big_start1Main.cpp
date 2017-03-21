/***************************************************************
 * Name:      big_start1Main.cpp
 * Purpose:   Code for Application Frame
 * Author:    zyq ()
 * Created:   2014-05-12
 * Copyright: zyq ()
 * License:
 **************************************************************/

#include "big_start1Main.h"
#include <wx/msgdlg.h>
#include <wx/dcclient.h>
#include <wx/bitmap.h>
#include <wx/dcbuffer.h>
#include <wx/scrolwin.h>
#include <wx/timer.h>
#include <wx/graphics.h>
#include <wx/sound.h>
#include <wx/dialog.h>
#include "big_pointsDialog.h"
#define ID_TIMER


//(*InternalHeaders(big_startDialog)
#include <wx/intl.h>
#include <wx/string.h>
//*)

BEGIN_EVENT_TABLE(big_start1Dialog,wxDialog)
    //(*EventTable(big_startDialog)
    //*)
    EVT_PAINT(big_start1Dialog::OnPaint)
    EVT_KEY_DOWN(big_start1Dialog::OnKeyDown)
    EVT_TIMER(wxID_ANY,big_start1Dialog::Ontimer)
    EVT_ERASE_BACKGROUND(big_start1Dialog::OnEraseBackground)
    EVT_CLOSE(big_start1Dialog::OnQuit)
END_EVENT_TABLE()


big_start1Dialog::big_start1Dialog(wxWindow* parent,wxWindowID id):m_timer(this,wxID_ANY)
{
    //(*Initialize(big_startDialog)
    Create(parent, id, _("Plane Shoot"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("id"));
    SetClientSize(wxSize(800,600));
    Move(wxPoint(-1,-1));
    //*)
    Init();//��ʼ��
    m_timer.Start(100);//ϵͳˢ���ٶ�
}

big_start1Dialog::~big_start1Dialog()
{
    //(*Destroy(big_startDialog)
    //*)
}
void big_start1Dialog::SetModel(wxString model)
{
    m_model=model;
}

void big_start1Dialog::SetLevel(int level)
{
    m_level=level;
}

void big_start1Dialog::SetMusic(wxString music)
{
    m_music=music;
}

void big_start1Dialog::SetZhuangbei(int zidan,int zhadan,int fangdanyi,int lives)
{
    m_zidan=zidan;
    m_zhadan=zhadan;
    m_fangdanyi=fangdanyi;
    m_lives=lives;

}
int big_start1Dialog::Getscore()//��ȡ��Ϸ��߷ֲ�����
{
    return m_mscore[m_level-1];
}

void big_start1Dialog::Init()
{

    ResetObjects();//��ʼ����Ϸ����
    mycount=90;//��Ϸ������ϵͳˢ��90��
    for(int i=0;i<10;i++)//��ʼ����������߷�Ϊ0���ؿ�Ϊ1
    {m_score[i]=0;
    if(m_mscore[i]>2000||m_mscore[i]<0)
    m_mscore[i]=0;
    }
     if(m_level>9||m_level==1)
   {
       m_level=1;
       //m_music=wxT("1.wav");
   }

     //wxSound::Play(m_music, wxSOUND_ASYNC|wxSOUND_LOOP);
}

void big_start1Dialog::ResetObjects()
{
    m_gameover=false;//��Ϸû�н���
    m_player.x=240;//��ҷɻ���ʼ����Ϊ��240,400��
    m_player.y=400;
   for(int i=0;i<20;i++)//��ʼ����Ϸ��20����ͨ�л����꣨������֣�
   {
    m_enemies[i].x=rand()%460+20;
    m_enemies[i].y=-300-100*i;
   }
   for(int i=0;i<5;i++)//��ʼ����Ϸ��5������ɻ����꣨�����
   {
    m_enemies2[i].x=rand()%460+40;
    m_enemies2[i].y=-300-500*i;
   }
   for(int i=0;i<20;i++)//��ʼ���ӵ����꣬����ҷɻ���ͷ�����
   {
    m_ballet[i].x=m_player.x-180;
    m_ballet[i].y=-50-30*i;
   }
    m_ball.x=-5000;//�ɻ������еı�ըЧ������
    m_ball.y=-5000;
    this->Refresh(false);//ˢ�´���
}

void big_start1Dialog::OnQuit(wxCloseEvent& event)//�˳����ں���
{

    wxSound::Stop();//ֹͣ����
    if (IsModal())//�ر�ģ̬������
    {// EndModal(wxID_CANCEL);
      Destroy();
    }
}

void big_start1Dialog::OnAbout(wxCommandEvent& event)
{
}

void big_start1Dialog::OnPaint(wxPaintEvent& event)
{

    wxBufferedPaintDC dc(this);
    PrepareDC(dc);
    draw(dc);

}

void big_start1Dialog::OnKeyDown(wxKeyEvent& event)//���̰��º���
{
   switch(event.GetKeyCode())//��ȡ���̰�����Ϣ
   {
    case WXK_ALT://�����Ϸ��û��������alt����ҷɻ��������10������
       if(!m_gameover)
        {m_player.x-=10;}
    break;
    case WXK_SPACE://�����Ϸ��û�������¿ո����ҷɻ��������10������
       if(!m_gameover)
        {
          m_player.x+=10;
        }
    break;

    case WXK_CONTROL://�����Ϸû�н�����˫���ӵ���Ŀ����0������ctrl������˫���ӵ���ͬʱ˫���ӵ�����1
       if(!m_gameover&&m_zidan>0)
        {
           let1=true;
           balle=wxT("dzidan.png");
           m_zidan-=1;
        }
    break;

    case WXK_SHIFT://�����Ϸû�н�����ը����Ŀ����0������shift������ը����ͬʱը������1
       if(!m_gameover&&m_zhadan>0)
        {
           let2=true;
           for(i=0;i<20;i++)
           m_e[i]=1;
           for(i=0;i<5;i++)
           m_e2[i]=1;
           m_zhadan-=1;
        }
    break;

    case WXK_DELETE://�����Ϸû�н����ҷ�������Ŀ����0������delete��ʹ�÷����£�ͬʱ����������1
      if(!m_gameover&&m_fangdanyi>0)
        {
            let3=true;
            m_plane=wxT("guangquanplane.png");
            m_fangdanyi-=1;

        }
    break;
   }
   this->Refresh(false);

}

void big_start1Dialog::OnEraseBackground(wxEraseEvent& event)
{
}



void big_start1Dialog::draw(wxDC &dc)
{
     if(m_level>9)
   {
       m_level=1;
   }
   if(m_model==wxT(""))//û��ѡ��ģʽʱĬ��Ϊbc1
       m_model=wxT("bc1.png");
    if (m_zidan>100)//��ʼ��˫���ӵ���ը����������Ϊ0������Ϊ3
    m_zidan=0;
    if (m_zhadan>8)
    m_zhadan=0;
     if (m_fangdanyi<0||m_fangdanyi>10)
    m_fangdanyi=0;
    if (m_lives>100||m_lives==0)
    m_lives=3;
    if(balle==wxT(""))
    balle=wxT("ballet.png");//��ʼ���ӵ�ͼƬ
    wxBitmap bmp1(wxT("bc1.png"), wxBITMAP_TYPE_PNG);
    dc.DrawBitmap(bmp1, 0,0, true);//����Ϸ����ͼ
    wxBitmap bmp6(m_model, wxBITMAP_TYPE_PNG);
    dc.DrawBitmap(bmp6, 0,0, true);//���ѡ��ģʽ������ģʽ����Ϸ����ͼ
    wxBitmap bmp5(wxT("crash.png"), wxBITMAP_TYPE_PNG);
    dc.DrawBitmap(bmp5, m_ball.x,m_ball.y, true);//����ըЧ��ͼ
    wxBitmap bmp3(balle, wxBITMAP_TYPE_PNG);
    for(i=0;i<20;i++)//���ӵ�
    {
        if (m_ballet[i].y>-110) m_ballet[i].x=m_player.x-180;
    dc.DrawBitmap(bmp3, m_ballet[i].x,m_ballet[i].y, true);
    }
    if(m_plane==wxT(""))
    m_plane=wxT("plane.png");
    wxBitmap bmp2(m_plane, wxBITMAP_TYPE_PNG);
    dc.DrawBitmap(bmp2, m_player.x,m_player.y, true);//����ҷɻ�
    wxBitmap bmp4(wxT("plane2.png"), wxBITMAP_TYPE_PNG);
    for(j=0;j<20;j++)
    dc.DrawBitmap(bmp4, m_enemies[j].x,m_enemies[j].y, true);//����ͨ�л�
    wxBitmap bmp7(wxT("plane3.png"), wxBITMAP_TYPE_PNG);
    for(j=0;j<5;j++)
    dc.DrawBitmap(bmp7, m_enemies2[j].x,m_enemies2[j].y, true);//������л�
    DrawTextString(dc,wxString::Format(wxT("Current Scores:%2i"), m_score[m_level-1]),10,10);//����Ϸ�������Ͻ�д��ǰ�÷�
    DrawTextString(dc,wxString::Format(wxT("Highest Scores:%2i"), m_mscore[m_level-1]),10,40);//����Ϸ�������Ͻ�д��ߵ÷�
    DrawTextString(dc,wxString::Format(wxT("Level:%2i"), m_level),10,70);//����Ϸ�������Ͻ�д��ǰ�ؿ�
    DrawTextString(dc,wxString::Format(wxT("%2i"), m_lives),60,104);//����Ϸ�������Ͻ�д��ǰ����
    DrawTextString(dc,wxString::Format(wxT("%2i"), m_zidan),60,148);//����Ϸ�������Ͻ�д��ǰ˫���ӵ���
    DrawTextString(dc,wxString::Format(wxT("%2i"), m_zhadan),60,187);//����Ϸ�������Ͻ�д��ǰը����
    DrawTextString(dc,wxString::Format(wxT("%2i"), m_fangdanyi),60,235);//����Ϸ�������Ͻ�д��ǰ��������
    //DrawTextString(dc,wxString::Format(m_music),100,70);
    DrawTextString(dc,wxString::Format(wxT("TIME LEFT: %2i"), mycount),650,10);//����Ϸ�������Ͻ�д����ʱ
    //DrawTextString(dc,wxString::Format(wxT("%2i,%2i"),m_enemies2[0].x,m_enemies2[0].y),600,70);
    //DrawTextString(dc,wxString::Format(wxT("%2i"),m_e[0]),600,80);
    //DrawTextString(dc,wxString::Format(wxT("%2i,%2i"),m_player.x,m_player.y),600,90);
    //DrawTextString(dc,wxString::Format(wxT("%2i,%2i"),m_enemies[0].x,m_enemies[0].y),600,110);
}


void big_start1Dialog::DrawTextString(wxDC& dc, const wxString& text,int x,int y)
{
  wxFont font(12, wxFONTFAMILY_DECORATIVE, wxNORMAL, wxBOLD);
  dc.SetFont(font);
  dc.SetBackgroundMode(wxTRANSPARENT);
  dc.SetTextForeground(*wxBLACK);
  dc.SetTextBackground(*wxWHITE);
  dc.DrawText(text,x,y);
}

void big_start1Dialog::Ontimer(wxTimerEvent& event)//ÿ��ϵͳˢ�¶�����
{
for(i=0;i<20;i++)//�ӵ���ǰ��
{
    m_ballet[i].y-=10;
    if(m_ballet[i].y<-652)
        m_ballet[i].y=-50;
        this->Refresh(false);
}
for(int m=0;m<20;m++)//��ͨ�л���ǰ��
{m_enemies[m].y+=10;
if(m_enemies[m].y>602)
        m_enemies[m].y=-300;
        this->Refresh(false);
}
for(int m=0;m<5;m++)//����л���ǰ��
{m_enemies2[m].y+=10;
if(m_enemies2[m].y>602)
        m_enemies2[m].y=-300;
        this->Refresh(false);
}
 m_j=0;m_i=0;
for(j=0;j<20;j++)
  for(i=0;i<20;i++)

{  if(let2)//���ʹ��ը�������еĵл����е�
     {
        if(m_e[j]==1)
        {
            m_ball.x=m_enemies[j].x+80;//��ըЧ��ͼ�ƶ�������ĵл�λ��
            m_ball.y=m_enemies[j].y+60;

                  m_enemies[j].x=2000;//����ĵл�x�����Ƶ�Զ��
                  m_score[m_level-1]+=100;//ÿ����һ�ܵл�������100

        }
     }
    if(let1)//���ʹ��˫���ӵ�
     {m_e[j]=Crashdouble(m_ballet[i].x,m_enemies[j].x,m_ballet[i].y,m_enemies[j].y);//����Crashdouble����������m_e[j]��ֵ
        if(m_e[j]==1)
        {m_ball.x=m_enemies[j].x+80;
        m_ball.y=m_enemies[j].y+60;
        m_enemies[j].x=2000;
        m_score[m_level-1]+=100;

        }
    }
    else
    {
         if(!let2)//���û��ʹ�÷�����

        m_e[j]=Crash(m_ballet[i].x,m_enemies[j].x,m_ballet[i].y,m_enemies[j].y);//����Crash����������m_e[j]��ֵ
        if(m_e[j]==1)
        {m_ball.x=m_enemies[j].x+80;
        m_ball.y=m_enemies[j].y+60;
        m_enemies[j].x=2000;
        m_score[m_level-1]+=100;
        }
    }

}
for(j=0;j<5;j++)
  for(i=0;i<5;i++)

{  if(let2)
     {
        if(m_e2[j]==1)
        {
            m_ball.x=m_enemies2[j].x+80;
            m_ball.y=m_enemies2[j].y+60;

              //    m_enemies2[j].x=2000;
                  m_score[m_level-1]+=200;//��������л�������2000

        }
     }
    if(let1)
     {m_e2[j]=Crashdouble(m_ballet[i].x,m_enemies2[j].x,m_ballet[i].y,m_enemies2[j].y);
        if(m_e2[j]==1)
        {m_ball.x=m_enemies2[j].x+80;
        m_ball.y=m_enemies2[j].y+60;
        m_enemies2[j].x=2000;
        m_score[m_level-1]+=200;

        }
    }
    else
    {
         if(!let2)

        m_e2[j]=Crash2(m_ballet[i].x,m_enemies2[j].x,m_ballet[i].y,m_enemies2[j].y);
        if(m_e2[j]==1)
        {m_ball.x=m_enemies2[j].x-160;
        m_ball.y=m_enemies2[j].y-120;
        m_enemies2[j].x=2000;
        m_score[m_level-1]+=200;
        }
    }

}
    let2=0;
if(!let3)//���û��ʹ�÷�����
{for(j=0;j<20;j++)
   {
       m_m[j]=Crashme(m_player.x,m_enemies[j].x,m_player.y,m_enemies[j].y);//����rashme����������m_m[j]��ֵ
       if(m_m[j]==2)
        {m_ball.x=m_player.x-20;
        m_ball.y=m_player.y;
        m_player.x=2000;
        m_gameover=false;
        m_lives-=1;//������������1
        if(m_lives==2)//�����ʣ2��������ҷɻ���Ϊǳ��ɫ
            m_plane=wxT("plane_g.png");
        if(m_lives==1)//�����ʣ1��������ҷɻ���Ϊ����ɫ
            m_plane=wxT("plane_sg.png");
        if(m_lives==0)//û����ʱ
        {
            if(m_score[m_level-1]>m_mscore[m_level-1])//��¼����߷�
                m_mscore[m_level-1]=m_score[m_level-1];
        wxMessageBox(wxString::Format(wxT("GAME OVER!\nCurrent Score:%2i"), m_score[m_level-1]));//��ʾGameover
            EndModal(wxID_CANCEL);//�رմ���
        }
        else
        {wxMessageBox(wxString::Format(wxT("%2i Lives Left!"), m_lives));//����������ÿ�α����к���ʾ��ʣ��������������������Ϸ����
        ResetObjects();}
          this->Refresh(false);
        }

   }

   for(j=0;j<5;j++)
   {
       m_m2[j]=Crashme2(m_player.x,m_enemies2[j].x,m_player.y,m_enemies2[j].y);
       if(m_m2[j]==2)
        {m_ball.x=m_player.x-20;
        m_ball.y=m_player.y;
        m_player.x=2000;
        m_gameover=false;
        m_lives-=1;
        if(m_lives==2)
            m_plane=wxT("plane_g.png");
        if(m_lives==1)
            m_plane=wxT("plane_sg.png");
        if(m_lives==0)
        {
            if(m_score[m_level-1]>m_mscore[m_level-1])
                m_mscore[m_level-1]=m_score[m_level-1];
        wxMessageBox(wxString::Format(wxT("GAME OVER!\nCurrent Score:%2i"), m_score[m_level-1]));
            EndModal(wxID_CANCEL);
        }
        else
        {wxMessageBox(wxString::Format(wxT("%2i Lives Left!"), m_lives));
        ResetObjects();}
          this->Refresh(false);
        }

   }

}
   mycount--;//ÿˢ��һ�μ�������1
     if(m_score[m_level-1]>m_mscore[m_level-1])//��¼��߷�
    {m_mscore[m_level-1]=m_score[m_level-1];
//    m_call->SetScore(m_mscore[m_level-1]);
    }
   if(mycount==0)//�����������0ֹͣ����
   {
    wxSound::Stop();
    if (IsModal())//�رմ���
    {// EndModal(wxID_CANCEL);
      Destroy();
    }
   }

}

void big_start1Dialog::explode()//��ը����
{
    if (m_ballet[i].y<400)
    for(j=0;j<20;j++)
        for(i=0;i<40;i++)
            if (m_ballet[i].x==m_enemies[j].x&&m_enemies[j].y==m_ballet[i].y+30*i)
            {}
    for(j=0;j<5;j++)
        for(i=0;i<40;i++)
            if (m_ballet[i].x==m_enemies2[j].x&&m_enemies2[j].y==m_ballet[i].y+30*i)
            {}
}

int big_start1Dialog::Crash(int x1,int x2,int y1,int y2)//��ͨ�л�������
{
	if(x1>=x2-71)   m_e[j]=x1+71-x2;
	else   m_e[j]=x2-x1-71;//��¼���λ�ò�
    if(m_e[j]<35&&y1-y2<-270&&y2>-280) return 1;//����ӵ���л�λ������ڸ÷�Χ�ڷ���1�����򷵻�0
    else   return 0;
}

int big_start1Dialog::Crash2(int x1,int x2,int y1,int y2)//����л�������
{
	if(x1>=x2-300)   m_e2[j]=x1-x2+300;
	else   m_e2[j]=-x1+x2-300;
    if(m_e2[j]<30&&y1-y2<-270&&y2>-280)
    return 1;
    else   return 0;
}

int big_start1Dialog::Crashme(int x1,int x2,int y1,int y2)//��ҷɻ�����ͨ�л�ײ
{
    int dx;//��¼���λ�ò�
    if(x1>=x2+109)   dx=x1-109-x2;
	else   dx=x2-x1+109;
   if(dx<60&&y2>260) return 2;//������λ�ò��ڸ÷�Χ�ڷ���2�����򷵻�0
    else   return 0;

}

int big_start1Dialog::Crashme2(int x1,int x2,int y1,int y2)//��ҷɻ�������л�ײ
{
    int dx;
    if(x1>=x2+109)   dx=x1-109-x2;
	else   dx=x2-x1+109;
   if(dx<60&&y2>260) return 2;
    else   return 0;

}

int big_start1Dialog::Crashdouble(int x1,int x2,int y1,int y2)//�л���˫���ӵ�����
{
	if(x1>=x2-71)   m_e[j]=x1+71-x2;
	else   m_e[j]=x2-x1-71;
    if(m_e[j]<60&&y1-y2<-270&&y2>-280)
    return 1;
    else   return 0;
}
