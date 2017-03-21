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
    Init();//初始化
    m_timer.Start(100);//系统刷新速度
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
int big_start1Dialog::Getscore()//获取游戏最高分并返回
{
    return m_mscore[m_level-1];
}

void big_start1Dialog::Init()
{

    ResetObjects();//初始化游戏对象
    mycount=90;//游戏持续到系统刷新90次
    for(int i=0;i<10;i++)//初始化分数和最高分为0，关卡为1
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
    m_gameover=false;//游戏没有结束
    m_player.x=240;//玩家飞机初始坐标为（240,400）
    m_player.y=400;
   for(int i=0;i<20;i++)//初始化游戏中20架普通敌机坐标（随机出现）
   {
    m_enemies[i].x=rand()%460+20;
    m_enemies[i].y=-300-100*i;
   }
   for(int i=0;i<5;i++)//初始化游戏中5架特殊飞机坐标（随机）
   {
    m_enemies2[i].x=rand()%460+40;
    m_enemies2[i].y=-300-500*i;
   }
   for(int i=0;i<20;i++)//初始化子弹坐标，从玩家飞机的头部打出
   {
    m_ballet[i].x=m_player.x-180;
    m_ballet[i].y=-50-30*i;
   }
    m_ball.x=-5000;//飞机被打中的爆炸效果坐标
    m_ball.y=-5000;
    this->Refresh(false);//刷新窗口
}

void big_start1Dialog::OnQuit(wxCloseEvent& event)//退出窗口函数
{

    wxSound::Stop();//停止音乐
    if (IsModal())//关闭模态化窗口
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

void big_start1Dialog::OnKeyDown(wxKeyEvent& event)//键盘按下函数
{
   switch(event.GetKeyCode())//获取键盘按下信息
   {
    case WXK_ALT://如果游戏还没结束按下alt键玩家飞机横坐标减10，左移
       if(!m_gameover)
        {m_player.x-=10;}
    break;
    case WXK_SPACE://如果游戏还没结束按下空格键玩家飞机横坐标加10，右移
       if(!m_gameover)
        {
          m_player.x+=10;
        }
    break;

    case WXK_CONTROL://如果游戏没有结束且双排子弹数目大于0，按下ctrl键发射双排子弹，同时双排子弹数减1
       if(!m_gameover&&m_zidan>0)
        {
           let1=true;
           balle=wxT("dzidan.png");
           m_zidan-=1;
        }
    break;

    case WXK_SHIFT://如果游戏没有结束且炸弹数目大于0，按下shift键发射炸弹，同时炸弹数减1
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

    case WXK_DELETE://如果游戏没有结束且防弹衣数目大于0，按下delete键使用防弹衣，同时防弹衣数减1
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
   if(m_model==wxT(""))//没有选择模式时默认为bc1
       m_model=wxT("bc1.png");
    if (m_zidan>100)//初始化双排子弹、炸弹、防弹衣为0，命数为3
    m_zidan=0;
    if (m_zhadan>8)
    m_zhadan=0;
     if (m_fangdanyi<0||m_fangdanyi>10)
    m_fangdanyi=0;
    if (m_lives>100||m_lives==0)
    m_lives=3;
    if(balle==wxT(""))
    balle=wxT("ballet.png");//初始化子弹图片
    wxBitmap bmp1(wxT("bc1.png"), wxBITMAP_TYPE_PNG);
    dc.DrawBitmap(bmp1, 0,0, true);//画游戏背景图
    wxBitmap bmp6(m_model, wxBITMAP_TYPE_PNG);
    dc.DrawBitmap(bmp6, 0,0, true);//如果选过模式，按照模式画游戏背景图
    wxBitmap bmp5(wxT("crash.png"), wxBITMAP_TYPE_PNG);
    dc.DrawBitmap(bmp5, m_ball.x,m_ball.y, true);//画爆炸效果图
    wxBitmap bmp3(balle, wxBITMAP_TYPE_PNG);
    for(i=0;i<20;i++)//画子弹
    {
        if (m_ballet[i].y>-110) m_ballet[i].x=m_player.x-180;
    dc.DrawBitmap(bmp3, m_ballet[i].x,m_ballet[i].y, true);
    }
    if(m_plane==wxT(""))
    m_plane=wxT("plane.png");
    wxBitmap bmp2(m_plane, wxBITMAP_TYPE_PNG);
    dc.DrawBitmap(bmp2, m_player.x,m_player.y, true);//画玩家飞机
    wxBitmap bmp4(wxT("plane2.png"), wxBITMAP_TYPE_PNG);
    for(j=0;j<20;j++)
    dc.DrawBitmap(bmp4, m_enemies[j].x,m_enemies[j].y, true);//画普通敌机
    wxBitmap bmp7(wxT("plane3.png"), wxBITMAP_TYPE_PNG);
    for(j=0;j<5;j++)
    dc.DrawBitmap(bmp7, m_enemies2[j].x,m_enemies2[j].y, true);//画特殊敌机
    DrawTextString(dc,wxString::Format(wxT("Current Scores:%2i"), m_score[m_level-1]),10,10);//在游戏背景左上角写当前得分
    DrawTextString(dc,wxString::Format(wxT("Highest Scores:%2i"), m_mscore[m_level-1]),10,40);//在游戏背景左上角写最高得分
    DrawTextString(dc,wxString::Format(wxT("Level:%2i"), m_level),10,70);//在游戏背景左上角写当前关卡
    DrawTextString(dc,wxString::Format(wxT("%2i"), m_lives),60,104);//在游戏背景左上角写当前命数
    DrawTextString(dc,wxString::Format(wxT("%2i"), m_zidan),60,148);//在游戏背景左上角写当前双排子弹数
    DrawTextString(dc,wxString::Format(wxT("%2i"), m_zhadan),60,187);//在游戏背景左上角写当前炸弹数
    DrawTextString(dc,wxString::Format(wxT("%2i"), m_fangdanyi),60,235);//在游戏背景左上角写当前防弹衣数
    //DrawTextString(dc,wxString::Format(m_music),100,70);
    DrawTextString(dc,wxString::Format(wxT("TIME LEFT: %2i"), mycount),650,10);//在游戏背景右上角写倒计时
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

void big_start1Dialog::Ontimer(wxTimerEvent& event)//每次系统刷新都会做
{
for(i=0;i<20;i++)//子弹向前走
{
    m_ballet[i].y-=10;
    if(m_ballet[i].y<-652)
        m_ballet[i].y=-50;
        this->Refresh(false);
}
for(int m=0;m<20;m++)//普通敌机向前走
{m_enemies[m].y+=10;
if(m_enemies[m].y>602)
        m_enemies[m].y=-300;
        this->Refresh(false);
}
for(int m=0;m<5;m++)//特殊敌机向前走
{m_enemies2[m].y+=10;
if(m_enemies2[m].y>602)
        m_enemies2[m].y=-300;
        this->Refresh(false);
}
 m_j=0;m_i=0;
for(j=0;j<20;j++)
  for(i=0;i<20;i++)

{  if(let2)//如果使用炸弹，所有的敌机都中弹
     {
        if(m_e[j]==1)
        {
            m_ball.x=m_enemies[j].x+80;//爆炸效果图移动到被打的敌机位置
            m_ball.y=m_enemies[j].y+60;

                  m_enemies[j].x=2000;//被打的敌机x坐标移到远处
                  m_score[m_level-1]+=100;//每打中一架敌机分数加100

        }
     }
    if(let1)//如果使用双排子弹
     {m_e[j]=Crashdouble(m_ballet[i].x,m_enemies[j].x,m_ballet[i].y,m_enemies[j].y);//调用Crashdouble函数，返回m_e[j]的值
        if(m_e[j]==1)
        {m_ball.x=m_enemies[j].x+80;
        m_ball.y=m_enemies[j].y+60;
        m_enemies[j].x=2000;
        m_score[m_level-1]+=100;

        }
    }
    else
    {
         if(!let2)//如果没有使用防弹衣

        m_e[j]=Crash(m_ballet[i].x,m_enemies[j].x,m_ballet[i].y,m_enemies[j].y);//调用Crash函数，返回m_e[j]的值
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
                  m_score[m_level-1]+=200;//打中特殊敌机分数加2000

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
if(!let3)//如果没有使用防弹衣
{for(j=0;j<20;j++)
   {
       m_m[j]=Crashme(m_player.x,m_enemies[j].x,m_player.y,m_enemies[j].y);//调用rashme函数，返回m_m[j]的值
       if(m_m[j]==2)
        {m_ball.x=m_player.x-20;
        m_ball.y=m_player.y;
        m_player.x=2000;
        m_gameover=false;
        m_lives-=1;//被打中命数减1
        if(m_lives==2)//如果还剩2条命，玩家飞机变为浅绿色
            m_plane=wxT("plane_g.png");
        if(m_lives==1)//如果还剩1条命，玩家飞机变为深绿色
            m_plane=wxT("plane_sg.png");
        if(m_lives==0)//没有命时
        {
            if(m_score[m_level-1]>m_mscore[m_level-1])//记录下最高分
                m_mscore[m_level-1]=m_score[m_level-1];
        wxMessageBox(wxString::Format(wxT("GAME OVER!\nCurrent Score:%2i"), m_score[m_level-1]));//提示Gameover
            EndModal(wxID_CANCEL);//关闭窗口
        }
        else
        {wxMessageBox(wxString::Format(wxT("%2i Lives Left!"), m_lives));//若还有命，每次被打中后提示还剩的命数，并重新设置游戏对象
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
   mycount--;//每刷新一次计数减少1
     if(m_score[m_level-1]>m_mscore[m_level-1])//记录最高分
    {m_mscore[m_level-1]=m_score[m_level-1];
//    m_call->SetScore(m_mscore[m_level-1]);
    }
   if(mycount==0)//如果计数等于0停止音乐
   {
    wxSound::Stop();
    if (IsModal())//关闭窗口
    {// EndModal(wxID_CANCEL);
      Destroy();
    }
   }

}

void big_start1Dialog::explode()//爆炸函数
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

int big_start1Dialog::Crash(int x1,int x2,int y1,int y2)//普通敌机被打中
{
	if(x1>=x2-71)   m_e[j]=x1+71-x2;
	else   m_e[j]=x2-x1-71;//记录相对位置差
    if(m_e[j]<35&&y1-y2<-270&&y2>-280) return 1;//如果子弹与敌机位置相差在该范围内返回1，否则返回0
    else   return 0;
}

int big_start1Dialog::Crash2(int x1,int x2,int y1,int y2)//特殊敌机被打中
{
	if(x1>=x2-300)   m_e2[j]=x1-x2+300;
	else   m_e2[j]=-x1+x2-300;
    if(m_e2[j]<30&&y1-y2<-270&&y2>-280)
    return 1;
    else   return 0;
}

int big_start1Dialog::Crashme(int x1,int x2,int y1,int y2)//玩家飞机被普通敌机撞
{
    int dx;//记录相对位置差
    if(x1>=x2+109)   dx=x1-109-x2;
	else   dx=x2-x1+109;
   if(dx<60&&y2>260) return 2;//如果相对位置差在该范围内返回2，否则返回0
    else   return 0;

}

int big_start1Dialog::Crashme2(int x1,int x2,int y1,int y2)//玩家飞机被特殊敌机撞
{
    int dx;
    if(x1>=x2+109)   dx=x1-109-x2;
	else   dx=x2-x1+109;
   if(dx<60&&y2>260) return 2;
    else   return 0;

}

int big_start1Dialog::Crashdouble(int x1,int x2,int y1,int y2)//敌机被双排子弹打中
{
	if(x1>=x2-71)   m_e[j]=x1+71-x2;
	else   m_e[j]=x2-x1-71;
    if(m_e[j]<60&&y1-y2<-270&&y2>-280)
    return 1;
    else   return 0;
}
