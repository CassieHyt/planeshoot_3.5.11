/***************************************************************
 * Name:      big_startMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    zyq ()
 * Created:   2014-05-12
 * Copyright: zyq ()
 * License:
 **************************************************************/

#include "big_startMain.h"
#include <wx/msgdlg.h>
#include <wx/dcclient.h>
#include <wx/sound.h>
#include <wx/bitmap.h>
#include <wx/dcbuffer.h>
#include <wx/scrolwin.h>
#include <wx/bmpbuttn.h>
#include "big_shopDialog.h"
#include "big_musicDialog.h"
#include "big_modelDialog.h"
#include "big_pointsDialog.h"
#include "big_start1Main.h"
#include <wx/mediactrl.h>


//(*InternalHeaders(big_startDialog)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

//(*IdInit(big_startDialog)
//*)

BEGIN_EVENT_TABLE(big_startDialog,wxDialog)//事件列表
    //(*EventTable(big_startDialog)
    //*)
    EVT_PAINT(big_startDialog::OnPaint)
    EVT_ERASE_BACKGROUND(big_startDialog::OnEraseBackground)
END_EVENT_TABLE()



big_startDialog::big_startDialog(wxWindow* parent,wxWindowID id) //构造函数
{
    //(*Initialize(big_startDialog)
    Create(parent, id, _("Plane Shoot"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE|wxCLOSE_BOX, _T("id"));
    SetClientSize(wxSize(800,600));
    Move(wxPoint(-1,-1));
    Connect(wxEVT_MOTION,(wxObjectEventFunction)&big_startDialog::OnMouseMove);  //鼠标移动函数连接
    Connect(wxEVT_LEFT_UP,(wxObjectEventFunction)&big_startDialog::OnLeftUp);//鼠标左键松开（点击）函数连接
    //*)
    if(m_level==1) //初始化游戏界面音乐
        m_music=wxT("1.wav");

}

big_startDialog::~big_startDialog() // 析构函数
{
    //(*Destroy(big_startDialog)
    //*)
}

void big_startDialog::DrawTextString1(wxDC& dc, const wxString& text,wxCoord  x, wxCoord  y ) //在背景图上写字
{
wxFont font(10, wxFONTFAMILY_ROMAN, wxITALIC, wxBOLD);//设定字体、大小
dc.SetFont(font);
dc.SetBackgroundMode(wxTRANSPARENT);
dc.SetTextForeground(*wxBLACK);//前景色
dc.SetTextBackground(*wxWHITE);//背景色
dc.DrawText(text, x,y);
}

void big_startDialog::OnPaint(wxPaintEvent& event)//画图
{
wxBufferedPaintDC dc(this);//定义设备

PrepareDC(dc);

wxBitmap background(wxT("start.png"), wxBITMAP_TYPE_PNG);//主窗口背景图
dc.DrawBitmap(background, 0,0, true);
wxBitmap Start(wxT("T_start.png"), wxBITMAP_TYPE_PNG);//start图标
dc.DrawBitmap(Start, 330,240, true);
wxBitmap music(wxT("instruction.png"), wxBITMAP_TYPE_PNG);//说明图标
dc.DrawBitmap(music,200,370, true);
wxBitmap shop(wxT("shop.png"), wxBITMAP_TYPE_PNG);//商店图标
dc.DrawBitmap(shop,-10,110, true);
wxBitmap model(wxT("model.png"), wxBITMAP_TYPE_PNG);//模式图标
dc.DrawBitmap(model,170,170, true);
wxBitmap points(wxT("points.png"), wxBITMAP_TYPE_PNG);//关卡图标
dc.DrawBitmap(points,295,158, true);

//DrawTextString1(dc,wxString::Format(wxT("Highest Scores:%2i"), m_mscore[m_level-1]),60,10);
//DrawTextString1(dc,wxString::Format(wxT("Level:%2i"), m_level),5,10);
DrawTextString1(dc,m_note,note_x,note_y);//鼠标移动到上述图标时显示各图标含义
}



void big_startDialog::OnEraseBackground(wxEraseEvent& event)
{
}

void big_startDialog::SetModel(wxString model)//设置模式
{
    m_model=model;//使得当前关卡与传入关卡相同
}

void big_startDialog::SetScore(int mscore)//设置最高分
{
    m_mscore[m_level-1]=mscore;//使得当前最高分与传入最高分相同

}


void big_startDialog::SetZhuangbei(int zidan,int zhadan,int fangdanyi,int lives)//设置双排子弹、炸弹、防弹衣、命的个数，使得与传入值相同
{
    m_zidan=zidan;
    m_zhadan=zhadan;
    m_fangdanyi=fangdanyi;
    m_lives=lives;

}

void big_startDialog::SetLevel(int level)//设置关卡，使得与传入值相同
{
    m_level=level;

}

void big_startDialog::SetMusic(wxString music)//设置背景音乐，使得与传入值相同
{
    m_music=music;

}

void big_startDialog::OnInit(wxInitDialogEvent& event)
{

}



void big_startDialog::OnMouseMove(wxMouseEvent& event)//鼠标移动函数
{
    int x=event.GetX();//获得当前鼠标位置的x值
    int y=event.GetY();//获得当前鼠标位置的y值
    m_note=wxT(" ");
    note_x=1000;
    note_y=1000;//初始化m_note是空字符串，坐标在(1000,1000)
    bool a;
    a=(x>=343&&x<=456&&y>=249&&y<=280)||(x>=200&&x<=245&&y>=364&&y<=420)||(x>=312&&x<=358&&y>=379&&y<=420)||(x>=407&&x<=464&&y>=372&&y<=428)||(x>=518&&x<=570&&y>=380&&y<=427);

    if(x>=343&&x<=456&&y>=249&&y<=280)//如果鼠标在该范围内（start上）鼠标图案变成小手
    {
        this->SetCursor(wxImage("cursor.png"));
    }
    if(x>=200&&x<=245&&y>=364&&y<=420)//如果鼠标在该范围内（说明图标上）鼠标图案变成小手，并在旁边显示Instruction字样
    {
        m_note=wxT("Instruction");
        note_x=245;
        note_y=364;
        this->SetCursor(wxImage("cursor.png"));
    }

    if(x>=312&&x<=358&&y>=379&&y<=420)//如果鼠标在该范围内（商店图标上）鼠标图案变成小手，并在旁边显示Shop字样
    {
        m_note=wxT("Shop");
        note_x=358;
        note_y=365;
        this->SetCursor(wxImage("cursor.png"));
    }

    if(x>=407&&x<=464&&y>=372&&y<=428)//如果鼠标在该范围内（模式图标上）鼠标图案变成小手，并在旁边显示Model字样
    {
        m_note=wxT("Model");
        note_x=464;
        note_y=372;
        this->SetCursor(wxImage("cursor.png"));
    }

    if(x>=518&&x<=570&&y>=380&&y<=427)//如果鼠标在该范围内（关卡图标上）鼠标图案变成小手，并在旁边显示Level字样
    {
        m_note=wxT("Level");
        note_x=550;
        note_y=360;
        this->SetCursor(wxImage("cursor.png"));
    }

    if(!a)//如果鼠标不在以上范围内鼠标图案变成箭头且注释的坐标移到远处
    {
        m_note=wxT(" ");
        note_x=1000;
        note_y=1000;
        this->SetCursor(wxImage("mouse.png"));
    }
this->Refresh();//完成以上动作后刷新窗口
    //if(event.ButtonUp(wxMOUSE_BTN_LEFT))
      //  wxMessageBox(wxString::Format(_T("%d,%d"),x,y));

}

void big_startDialog::OnLeftUp(wxMouseEvent& event)//鼠标左键抬起函数
{
   int x=event.GetX();
    int y=event.GetY();//先获得鼠标位置
    //if(event.Button(wxMOUSE_BTN_LEFT))

  if(x>=343&&x<=456&&y>=249&&y<=280)    //在Start字样上
    {
    big_start1Dialog *startdialog=new big_start1Dialog(this);//创建一个新的游戏窗口
    startdialog->SetModel(m_model);//调用SetModel函数，设置模式，使新窗口的指针指向该值
    startdialog->SetLevel(m_level);//调用SetLevel函数，设置关卡，使新窗口的指针指向该值
    startdialog->SetMusic(m_music);//调用SetMusic函数，设置背景音乐，使新窗口的指针指向该值
    startdialog->SetZhuangbei(m_zidan,m_zhadan,m_fangdanyi,m_lives);//调用SethZuangbei函数，设置双排子弹、炸弹、防弹衣、命数，使新窗口的指针指向该值
    m_mscore[m_level-1]=startdialog->Getscore();
    wxSound::Play(m_music, wxSOUND_ASYNC|wxSOUND_LOOP);//播放背景音乐
       startdialog->ShowModal();//创建模态化游戏窗口
       }

  if(x>=200&&x<=245&&y>=364&&y<=420)   //在说明图标上
   {
       big_musicDialog *musicdialog=new big_musicDialog(this);//创建一个新的说明窗口
       musicdialog->ShowModal();//模态化显示窗口
    }



  if(x>=312&&x<=358&&y>=379&&y<=420)   //在商店图标上
    {
       big_shopDialog *shopdialog=new big_shopDialog(this);//创建一个新的商店窗口
       shopdialog->SetCall(this);//将该窗口的由商店界面传入的关于商店的值传入游戏界面
       shopdialog->ShowModal();//打开模态化窗口
    }

  if(x>=407&&x<=464&&y>=372&&y<=428)  //在模式图标上
    {
       big_modelDialog *modeldialog=new big_modelDialog(this);//创建一个新的模式窗口
       modeldialog->SetCall(this);//将该窗口的由模式界面传入的关于模式的值传入游戏界面
       modeldialog->ShowModal();
    }

  if(x>=518&&x<=570&&y>=380&&y<=427)
    {
       big_pointsDialog *pointsdialog=new big_pointsDialog(this);//创建一个新的关卡窗口
       pointsdialog->SetCall(this);//将该窗口的由关卡界面传入的关于关卡的值传入游戏界面
      // pointsdialog->SetScore(m_mscore[m_level-1]);
       pointsdialog->ShowModal();
    }

}

