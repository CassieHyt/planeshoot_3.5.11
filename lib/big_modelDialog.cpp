#include "big_modelDialog.h"
#include <wx/dcbuffer.h>
#include <wx/msgdlg.h>
#include "big_start1Main.h"

//(*InternalHeaders(big_modelDialog)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(big_modelDialog)
//*)

BEGIN_EVENT_TABLE(big_modelDialog,wxDialog)//事件列表
	//(*EventTable(big_modelDialog)
	//*)
	EVT_PAINT(big_modelDialog::OnPaint)
    EVT_ERASE_BACKGROUND(big_modelDialog::OnEraseBackground)
END_EVENT_TABLE()

big_modelDialog::big_modelDialog(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)//构造函数
{
	//(*Initialize(big_modelDialog)
	Create(parent, id, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("id"));
	SetClientSize(wxSize(800,600));
	Move(wxDefaultPosition);
	//*)
	Connect(wxEVT_LEFT_UP,(wxObjectEventFunction)&big_modelDialog::OnLeftUp);//连接鼠标左键抬起方法
	Connect(wxEVT_MOTION,(wxObjectEventFunction)&big_modelDialog::OnMouseMove);//连接鼠标移动方法
}

big_modelDialog::~big_modelDialog()
{
	//(*Destroy(big_modelDialog)
	//*)
}

void DrawTextString2(wxDC& dc, const wxString& text,wxCoord  x, wxCoord  y )//在窗口中写字
{
wxFont font(24, wxFONTFAMILY_SWISS, wxITALIC, wxBOLD);
dc.SetFont(font);
dc.SetBackgroundMode(wxTRANSPARENT);
dc.SetTextForeground(*wxBLACK);
dc.SetTextBackground(*wxWHITE);
dc.DrawText(text, x,y);
}

void big_modelDialog::OnPaint(wxPaintEvent& event)
{
wxBufferedPaintDC dc(this);

PrepareDC(dc);

wxBitmap modelbackground(wxT("modelbackground.png"), wxBITMAP_TYPE_PNG);
dc.DrawBitmap(modelbackground, 0,0, true);//画背景图
DrawTextString2(dc,wxString(wxT("Model:")),120,20);//显示当前选中的模式

DrawTextString2(dc,wxString(m_model),230,20);
}

void big_modelDialog::OnEraseBackground(wxEraseEvent& event)
{
}

void big_modelDialog::OnQuit(wxCommandEvent& event)
{
    Close();
}


void big_modelDialog::OnMouseMove(wxMouseEvent& event)//鼠标移动函数
{
    int x=event.GetX();
    int y=event.GetY();
    bool a;
    a=((x>=183&&x<=257&&y>=247&&y<=346)||(x>=351&&x<=476&&y>=251&&y<=344)||(x>=562&&x<=652&&y>=248&&y<=347)||(x>=675&&x<=745&&y>=534&&y<=568));

    if(a)//鼠标在该范围内图标变成手型，反之变成箭头
    {
        this->SetCursor(wxImage("cursor.png"));
    }
    if(!a)
    {
        this->SetCursor(wxImage("mouse.png"));
    }
this->Refresh();

}

void big_modelDialog::OnLeftUp(wxMouseEvent& event)//鼠标左键按下选中相应的模式
{
    int x=event.GetX();
    int y=event.GetY();

    //if(event.Button(wxMOUSE_BTN_LEFT))
    if(x>=183&&x<=257&&y>=247&&y<=346)
        {m_model=wxT("Sleet.png");//选中雨雪交加模式


        //mn=1;
        }
    if(x>=351&&x<=476&&y>=251&&y<=344)
        {m_model=wxT("Cloudy.png");//选中乌云密布模式
        //mn=2;
        }
    if(x>=562&&x<=652&&y>=248&&y<=347)
        {m_model=wxT("Sunny.png");//选中晴空万里模式
        //mn=3;
        }
    this->Refresh(false);

    m_call->SetModel(m_model);//将选中的模式值传到big_startDialog窗口
    if(x>=675&&x<=745&&y>=534&&y<=568)//鼠标在该范围内点击左键关闭窗口
        {
            //wxMessageBox(wxString::Format(_T("%d,%d"),x,y));
            if ( IsModal() )
               EndModal(wxID_CANCEL);
        }


}


