#include "big_pointsDialog.h"
#include <wx/dcbuffer.h>
#include <wx/msgdlg.h>
#include "big_start1Main.h"


//(*InternalHeaders(big_pointsDialog)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(big_pointsDialog)
//*)


BEGIN_EVENT_TABLE(big_pointsDialog,wxDialog)
	//(*EventTable(big_pointsDialog)
	//*)
	EVT_PAINT(big_pointsDialog::OnPaint)
    EVT_ERASE_BACKGROUND(big_pointsDialog::OnEraseBackground)
END_EVENT_TABLE()

big_pointsDialog::big_pointsDialog(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(big_pointsDialog)
	Create(parent, id, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("id"));
	SetClientSize(wxSize(800,600));
	Move(wxDefaultPosition);
	//*)
	Connect(wxEVT_LEFT_UP,(wxObjectEventFunction)&big_pointsDialog::OnLeftUp);
	Connect(wxEVT_MOTION,(wxObjectEventFunction)&big_pointsDialog::OnMouseMove);
	Init();
}

big_pointsDialog::~big_pointsDialog()
{
	//(*Destroy(big_pointsDialog)
	//*)
}

void big_pointsDialog::Init()//初始化所有关卡最高分、后面7个关卡上锁的坐标
{
   // m_level=1;
    m_lock[0].x1=498;
	m_lock[0].y1=164;
	m_lock[1].x1=610;
	m_lock[1].y1=164;
	m_lock[6].x1=610;
	m_lock[6].y1=280;
	m_lock[5].x1=498;
	m_lock[5].y1=280;
    m_lock[4].x1=383;
	m_lock[4].y1=280;
	m_lock[3].x1=270;
	m_lock[3].y1=280;
	m_lock[2].x1=155;
	m_lock[2].y1=280;
	m_mscore[0]=1000;
	m_mscore[1]=1000;
	m_mscore[2]=1000;
	m_mscore[3]=1000;
	m_mscore[4]=0;
	m_mscore[5]=0;
	m_mscore[6]=0;
	m_mscore[7]=0;
	m_mscore[8]=0;
	m_mscore[9]=0;

}

void DrawTextString(wxDC& dc, const wxString& text,wxCoord  x, wxCoord  y )
{
wxFont font(24, wxFONTFAMILY_SWISS, wxITALIC, wxBOLD);
dc.SetFont(font);
dc.SetBackgroundMode(wxTRANSPARENT);
dc.SetTextForeground(*wxBLACK);
dc.SetTextBackground(*wxWHITE);
dc.DrawText(text, x,y);
}

void big_pointsDialog::SetScore(int mscore)//设置最高分
{
    m_mscore[m_level-1]=mscore;//当前关卡的最高分
}

void big_pointsDialog::OnPaint(wxPaintEvent& event)
{
wxBufferedPaintDC dc(this);

PrepareDC(dc);

wxBitmap pointsbackground(wxT("pointsbackground.png"), wxBITMAP_TYPE_PNG);
dc.DrawBitmap(pointsbackground, 0,0, true);//画背景图
int i;
wxBitmap lock(wxT("lock.png"), wxBITMAP_TYPE_PNG);

for(i=0;i<=6;i++)//在4-10关的图标上加锁
{
   dc.DrawBitmap(lock,m_lock[i].x1,m_lock[i].y1, true);
}
    if(m_level>10)//初始化关卡为1
    {m_level=1;
    m_music=wxT("1.wav");}
DrawTextString(dc,wxString::Format(wxT("Level:%2i"), m_level),100,20);//在窗口左上角显示选中关卡
//DrawTextString(dc,wxString::Format(wxT("hs:%2i"), m_mscore[m_level-1]),100,50);
}

void big_pointsDialog::OnEraseBackground(wxEraseEvent& event)
{
}

void big_pointsDialog::OnQuit(wxCommandEvent& event)
{
    Close();
}


void big_pointsDialog::OnMouseMove(wxMouseEvent& event)//鼠标移动到关卡图标上时更换鼠标图片
{
    int x=event.GetX();
    int y=event.GetY();
    bool a;
    a=((x>=137&&x<=228&&y>=159&&y<=240)||(x>=253&&x<=340&&y>=164&&y<=240)||(x>=367&&x<=455&&y>=162&&y<=240)||
       (x>=481&&x<=568&&y>=160&&y<=240)||(x>=595&&x<=680&&y>=162&&y<=240)||(x>=137&&x<=228&&y>=273&&y<=355)||
       (x>=251&&x<=343&&y>=274&&y<=355)||(x>=366&&x<=458&&y>=273&&y<=355)||(x>=479&&x<=573&&y>=275&&y<=355)||
       (x>=591&&x<=684&&y>=273&&y<=355)||(x>=675&&x<=745&&y>=534&&y<=568));
    if(a)
    {
        this->SetCursor(wxImage("cursor.png"));
    }
    if(!a)
    {
        this->SetCursor(wxImage("mouse.png"));
    }
this->Refresh();

}

void big_pointsDialog::OnLeftUp(wxMouseEvent& event)//鼠标左键按下选中关卡，同时选中关卡匹配的音乐（后7关需解锁）
{
   int x=event.GetX();
    int y=event.GetY();//获取鼠标坐标
    //if(event.Button(wxMOUSE_BTN_LEFT))
  if(x>=137&&x<=228&&y>=159&&y<=240)
  {
      m_level=1;
      m_music=wxT("1.wav");
  }

  if(x>=253&&x<=340&&y>=164&&y<=240)
  {
      m_level=2;
      m_music=wxT("2.wav");
  }

  if(x>=367&&x<=455&&y>=162&&y<=240)
  {
      m_level=3;
      m_music=wxT("3.wav");
  }

  if(x>=481&&x<=568&&y>=160&&y<=240&&m_mscore[2]>=500&&m_lock[0].x1<1000&&m_lock[0].y1<1000)//鼠标坐标对应关卡4，且关卡3的最高分达到500
  {
      m_lock[0].x1=m_lock[0].x1+1000;//锁的坐标加1000，移到远处，相当于解锁
      m_lock[0].y1=m_lock[0].y1+1000;
      m_level=4;//关卡变为4
      m_music=wxT("4.wav");//音乐变为第4关的音乐
  }
  if(x>=481&&x<=568&&y>=160&&y<=240&&m_mscore[2]<1000)//如果鼠标对应关卡4但是第三关最高分小于500，提示分数限制
    wxMessageBox(wxT("Score Limited! Cannot Unlock!"));

  if(x>=595&&x<=680&&y>=162&&y<=240&&m_mscore[3]>=1000&&m_lock[1].x1<1000&&m_lock[1].y1<1000)
  {
      m_lock[1].x1+=1000;
      m_lock[1].y1+=1000;
      m_level=5;
      m_music=wxT("5.wav");
  }
  if(x>=595&&x<=680&&y>=162&&y<=240&&m_mscore[3]<1000)
    wxMessageBox(wxT("Score Limited! Cannot Unlock!"));

  if(x>=137&&x<=228&&y>=273&&y<=355&&m_mscore[4]>=1000&&m_lock[2].x1<1000&&m_lock[2].y1<1000)
  {
      m_lock[2].x1+=1000;
      m_lock[2].y1+=1000;
      m_level=6;
      m_music=wxT("6.wav");
  }
  if(x>=137&&x<=228&&y>=273&&y<=355&&m_mscore[4]<1000)
    wxMessageBox(wxT("Score Limited! Cannot Unlock!"));

  if(x>=251&&x<=343&&y>=274&&y<=355&&m_mscore[5]>=1000&&m_lock[3].x1<1000&&m_lock[3].y1<1000)
  {
      m_lock[3].x1+=1000;
      m_lock[3].y1+=1000;
      m_level=7;
      m_music=wxT("7.wav");
  }
  if(x>=251&&x<=343&&y>=274&&y<=355&&m_mscore[5]<1000)
    wxMessageBox(wxT("Score Limited! Cannot Unlock!"));

  if(x>=366&&x<=458&&y>=273&&y<=355&&m_mscore[6]>=1000&&m_lock[4].x1<1000&&m_lock[4].y1<1000)
  {
      m_lock[4].x1+=1000;
      m_lock[4].y1+=1000;
      m_level=8;
      m_music=wxT("8.wav");
  }
  if(x>=366&&x<=458&&y>=273&&y<=355&&m_mscore[6]<1000)
    wxMessageBox(wxT("Score Limited! Cannot Unlock!"));


  if(x>=479&&x<=573&&y>=275&&y<=355&&m_mscore[7]>=1000&&m_lock[5].x1<1000&&m_lock[5].y1<1000)
  {
      m_lock[5].x1+=1000;
      m_lock[5].y1+=1000;
      m_level=9;
      m_music=wxT("9.wav");
  }
  if(x>=479&&x<=573&&y>=275&&y<=355&&m_mscore[7]<1000)
    wxMessageBox(wxT("Score Limited! Cannot Unlock!"));

  if(x>=591&&x<=684&&y>=273&&y<=355&&m_mscore[8]>=1000&&m_lock[6].x1<1000&&m_lock[6].y1<1000)
  {
      m_lock[6].x1+=1000;
      m_lock[6].y1+=1000;
      m_level=10;
      m_music=wxT("10.wav");
  }
  if(x>=591&&x<=684&&y>=273&&y<=35&&m_mscore[8]<1000)
    wxMessageBox(wxT("Score Limited! Cannot Unlock!"));
     m_call->SetLevel(m_level);//返回关卡值到big_startDialog窗口
     m_call->SetMusic(m_music);//返回音乐名到big_startDialog窗口
  this->Refresh(false);//窗口刷新



  if(x>=675&&x<=745&&y>=534&&y<=568)//如果鼠标对应返回箭头，关闭模态化窗口
    {
      //wxMessageBox(wxString::Format(_T("%d,%d"),x,y));
        if ( IsModal() )
            EndModal(wxID_CANCEL);
    }
}

