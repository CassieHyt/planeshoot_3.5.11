#include "big_musicDialog.h"
#include <wx/dcbuffer.h>
#include <wx/msgdlg.h>
#include <wx/mediactrl.h>
//(*InternalHeaders(big_musicDialog)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(big_musicDialog)
//*)

BEGIN_EVENT_TABLE(big_musicDialog,wxDialog)
	//(*EventTable(big_musicDialog)
	//*)
	EVT_PAINT(big_musicDialog::OnPaint)
    EVT_ERASE_BACKGROUND(big_musicDialog::OnEraseBackground)
    //EVT_MEDIA_LOADED(wxID_ANY,big_musicDialog::OnPlay)
END_EVENT_TABLE()

big_musicDialog::big_musicDialog(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(big_musicDialog)
	Create(parent, id, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("id"));
	SetClientSize(wxSize(800,600));
	Move(wxDefaultPosition);
	//*)
Connect(wxEVT_MOTION,(wxObjectEventFunction)&big_musicDialog::OnMouseMove);//��������ƶ�����
	Connect(wxEVT_LEFT_UP,(wxObjectEventFunction)&big_musicDialog::OnLeftUp);//����������̧�𷽷�

}

big_musicDialog::~big_musicDialog()
{
	//(*Destroy(big_musicDialog)
	//*)
}




void big_musicDialog::OnPaint(wxPaintEvent& event)
{
wxBufferedPaintDC dc(this);

PrepareDC(dc);

wxBitmap musicbackground(wxT("gameinstruction.png"), wxBITMAP_TYPE_PNG);
dc.DrawBitmap(musicbackground, 0,0, true);
}

void big_musicDialog::OnEraseBackground(wxEraseEvent& event)
{
}

void big_musicDialog::OnQuit(wxCommandEvent& event)
{
    Close();
}


void big_musicDialog::OnMouseMove(wxMouseEvent& event)//����ƶ�����
{
    int x=event.GetX();
    int y=event.GetY();//����������
    bool a;
    a=(x>=675&&x<=745&&y>=534&&y<=568);
    if(a)//�������ڸ÷�Χ�����ͼ�������ͣ���֮��ɼ�ͷ
    {
        this->SetCursor(wxImage("cursor.png"));
    }
    if(!a)
    {
        this->SetCursor(wxImage("mouse.png"));
    }
this->Refresh();

}

void big_musicDialog::OnLeftUp(wxMouseEvent& event)
{
   int x=event.GetX();
    int y=event.GetY();
    //if(event.Button(wxMOUSE_BTN_LEFT))
  if(x>=675&&x<=745&&y>=534&&y<=568)//�������ڸ÷�Χ�ڵ��������رո�ģ̬������
    {
      //wxMessageBox(wxString::Format(_T("%d,%d"),x,y));
        if ( IsModal() )
            EndModal(wxID_CANCEL);
    }
}
