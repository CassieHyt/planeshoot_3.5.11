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

BEGIN_EVENT_TABLE(big_modelDialog,wxDialog)//�¼��б�
	//(*EventTable(big_modelDialog)
	//*)
	EVT_PAINT(big_modelDialog::OnPaint)
    EVT_ERASE_BACKGROUND(big_modelDialog::OnEraseBackground)
END_EVENT_TABLE()

big_modelDialog::big_modelDialog(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)//���캯��
{
	//(*Initialize(big_modelDialog)
	Create(parent, id, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("id"));
	SetClientSize(wxSize(800,600));
	Move(wxDefaultPosition);
	//*)
	Connect(wxEVT_LEFT_UP,(wxObjectEventFunction)&big_modelDialog::OnLeftUp);//����������̧�𷽷�
	Connect(wxEVT_MOTION,(wxObjectEventFunction)&big_modelDialog::OnMouseMove);//��������ƶ�����
}

big_modelDialog::~big_modelDialog()
{
	//(*Destroy(big_modelDialog)
	//*)
}

void DrawTextString2(wxDC& dc, const wxString& text,wxCoord  x, wxCoord  y )//�ڴ�����д��
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
dc.DrawBitmap(modelbackground, 0,0, true);//������ͼ
DrawTextString2(dc,wxString(wxT("Model:")),120,20);//��ʾ��ǰѡ�е�ģʽ

DrawTextString2(dc,wxString(m_model),230,20);
}

void big_modelDialog::OnEraseBackground(wxEraseEvent& event)
{
}

void big_modelDialog::OnQuit(wxCommandEvent& event)
{
    Close();
}


void big_modelDialog::OnMouseMove(wxMouseEvent& event)//����ƶ�����
{
    int x=event.GetX();
    int y=event.GetY();
    bool a;
    a=((x>=183&&x<=257&&y>=247&&y<=346)||(x>=351&&x<=476&&y>=251&&y<=344)||(x>=562&&x<=652&&y>=248&&y<=347)||(x>=675&&x<=745&&y>=534&&y<=568));

    if(a)//����ڸ÷�Χ��ͼ�������ͣ���֮��ɼ�ͷ
    {
        this->SetCursor(wxImage("cursor.png"));
    }
    if(!a)
    {
        this->SetCursor(wxImage("mouse.png"));
    }
this->Refresh();

}

void big_modelDialog::OnLeftUp(wxMouseEvent& event)//����������ѡ����Ӧ��ģʽ
{
    int x=event.GetX();
    int y=event.GetY();

    //if(event.Button(wxMOUSE_BTN_LEFT))
    if(x>=183&&x<=257&&y>=247&&y<=346)
        {m_model=wxT("Sleet.png");//ѡ����ѩ����ģʽ


        //mn=1;
        }
    if(x>=351&&x<=476&&y>=251&&y<=344)
        {m_model=wxT("Cloudy.png");//ѡ�������ܲ�ģʽ
        //mn=2;
        }
    if(x>=562&&x<=652&&y>=248&&y<=347)
        {m_model=wxT("Sunny.png");//ѡ���������ģʽ
        //mn=3;
        }
    this->Refresh(false);

    m_call->SetModel(m_model);//��ѡ�е�ģʽֵ����big_startDialog����
    if(x>=675&&x<=745&&y>=534&&y<=568)//����ڸ÷�Χ�ڵ������رմ���
        {
            //wxMessageBox(wxString::Format(_T("%d,%d"),x,y));
            if ( IsModal() )
               EndModal(wxID_CANCEL);
        }


}


