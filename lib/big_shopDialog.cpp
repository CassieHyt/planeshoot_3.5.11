#include "big_shopDialog.h"
#include <wx/dcbuffer.h>
#include <wx/msgdlg.h>
#include <wx/checkbox.h>
#include "big_start1Main.h"

//(*InternalHeaders(big_shopDialog)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(big_shopDialog)
const long big_shopDialog::ID_CHECKBOX1 = wxNewId();
const long big_shopDialog::ID_CHECKBOX2 = wxNewId();
const long big_shopDialog::ID_CHECKBOX4 = wxNewId();
const long big_shopDialog::ID_CHECKBOX3 = wxNewId();
//*)

BEGIN_EVENT_TABLE(big_shopDialog,wxDialog)
	//(*EventTable(big_shopDialog)
	//*)
	EVT_PAINT(big_shopDialog::OnPaint)
    EVT_ERASE_BACKGROUND(big_shopDialog::OnEraseBackground)
END_EVENT_TABLE()

big_shopDialog::big_shopDialog(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(big_shopDialog)
	wxGridBagSizer* GridBagSizer1;

	Create(parent, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("wxID_ANY"));
	SetClientSize(wxSize(800,600));
	GridBagSizer1 = new wxGridBagSizer(0, 0);
	zidan = new wxCheckBox(this, ID_CHECKBOX1, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX1"));
	zidan->SetValue(false);
	GridBagSizer1->Add(zidan, wxGBPosition(15, 18), wxDefaultSpan, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	zhadan = new wxCheckBox(this, ID_CHECKBOX2, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX2"));
	zhadan->SetValue(false);
	GridBagSizer1->Add(zhadan, wxGBPosition(15, 29), wxDefaultSpan, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	feiji = new wxCheckBox(this, ID_CHECKBOX4, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX4"));
	feiji->SetValue(false);
	GridBagSizer1->Add(feiji, wxGBPosition(15, 49), wxDefaultSpan, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	fangdanyi = new wxCheckBox(this, ID_CHECKBOX3, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX3"));
	fangdanyi->SetValue(false);
	GridBagSizer1->Add(fangdanyi, wxGBPosition(15, 39), wxDefaultSpan, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SetSizer(GridBagSizer1);
	SetSizer(GridBagSizer1);
	Layout();

	Connect(ID_CHECKBOX1,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&big_shopDialog::OnCheckBox1Click);
	Connect(ID_CHECKBOX2,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&big_shopDialog::OnzhadanClick);
	Connect(ID_CHECKBOX4,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&big_shopDialog::OnfeijiClick);
	Connect(ID_CHECKBOX3,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&big_shopDialog::OnfangdanyiClick);
	Move(wxDefaultPosition);
	//*)
	Connect(wxEVT_LEFT_UP,(wxObjectEventFunction)&big_shopDialog::OnLeftUp);
	Connect(wxEVT_MOTION,(wxObjectEventFunction)&big_shopDialog::OnMouseMove);
	old_m_note=m_note;//��¼δ���в���ʱ���������֡�˫���ӵ���ը���������¡���
    old_m_zidan=m_zidan;
    old_m_lives=m_lives;
    old_m_zhadan=m_zhadan;
    old_m_fangdanyi=m_fangdanyi;
    Init();

}

big_shopDialog::~big_shopDialog()
{
	//(*Destroy(big_shopDialog)
	//*)
}

void big_shopDialog::DrawTextString(wxDC& dc, const wxString& text,wxCoord  x, wxCoord  y )
{
wxFont font(24, wxFONTFAMILY_SWISS, wxITALIC, wxBOLD);
dc.SetFont(font);
dc.SetBackgroundMode(wxTRANSPARENT);
dc.SetTextForeground(*wxBLACK);
dc.SetTextBackground(*wxWHITE);
dc.DrawText(text, x,y);
}

void big_shopDialog::OnPaint(wxPaintEvent& event)
{
wxBufferedPaintDC dc(this);

PrepareDC(dc);

wxBitmap shopbackground(wxT("shopbackground.png"), wxBITMAP_TYPE_PNG);
dc.DrawBitmap(shopbackground, 0,0, true);
//m_note=3200;
DrawTextString(dc,wxString::Format(wxT("Note:%2i"), m_note),100,20);
//DrawTextString1(dc,wxString::Format(wxT("zidan:%2i"), m_zidan),100,50);
//DrawTextString1(dc,wxString::Format(wxT("zhadan:%2i"), m_zhadan),160,20);
//DrawTextString1(dc,wxString::Format(wxT("get:%2i"),a),500,20);
}



void big_shopDialog::OnEraseBackground(wxEraseEvent& event)
{
}

void big_shopDialog::OnQuit(wxCommandEvent& event)
{
    Close();
}

void big_shopDialog::Init()//��ʼ��˫���ӵ���ը����������Ϊ0����Ϊ3
{
    if (m_zidan>100)
    m_zidan=0;
    if (m_zhadan>100)
    m_zhadan=0;
     if (m_fangdanyi>100)
    m_fangdanyi=0;
    if (m_lives>100)
    m_lives=3;
}


void big_shopDialog::OnMouseMove(wxMouseEvent& event)//����ƶ��������������ͼ��
{
    int x=event.GetX();
    int y=event.GetY();
    //wxMessageBox(wxString::Format(_T("%d,%d"),x,y));
     bool a;
    a=((x>=249&&x<=356&&y>=375&&y<=433)||(x>=429&&x<=540&&y>=369&&y<=430));

    if(x>=249&&x<=356&&y>=375&&y<=433)
    {
        this->SetCursor(wxImage("cursor.png"));
    }
    if(x>=429&&x<=540&&y>=369&&y<=430)
    {
        this->SetCursor(wxImage("cursor.png"));
    }
    if(!a)
    {
        this->SetCursor(wxImage("mouse.png"));
    }
this->Refresh();

}

void big_shopDialog::OnCheckBox1Click(wxCommandEvent& event)//˫���ӵ���ѡ��
{
    a=zidan->GetValue();//��ȡ�ø�ѡ���Ƿ�ѡ�е�ֵ
    if(a==1)//��ѡ�У�������һ��˫���ӵ���
    {
        m_note=m_note-500;//����һ��˫���ӵ��������ּ�500

        m_zidan=m_zidan+1;//˫���ӵ���1

        if(m_note<0)//�����������С��0��ʾ���ֲ���
            {wxMessageBox(wxT("Music Note Is Not Enough!"));
            if (wxOK)
                {m_note=m_note+500;
                zidan->SetValue(0);
                }
            }
    }
    if(a==0)//ѡ�к�ȡ�������֡�˫���ӵ����ָ�ԭֵ
    {
        m_note=m_note+500;
        m_zidan=m_zidan-1;
    }

    this->Refresh(false);

}

void big_shopDialog::OnzhadanClick(wxCommandEvent& event)//ը����ѡ����˫���ӵ���ͬ��������1000���֣�
{
    b=zhadan->GetValue();
    if(b==1)
    {
        m_note=m_note-1000;
        m_zhadan=m_zhadan+1;

        if(m_note<0)
            {wxMessageBox(wxT("Music Note Is Not Enough!"));
            if (wxOK)
                {m_note=m_note+1000;
                zhadan->SetValue(0);
                }
            }
    }
    if(b==0)
    {
        m_note=m_note+1000;
        m_zhadan=m_zhadan-1;
    }
    this->Refresh(false);

}

void big_shopDialog::OnfangdanyiClick(wxCommandEvent& event)//�����¸�ѡ�����Ļ���2000��
{
   c=fangdanyi->GetValue();
    if(c==1)
    {
        m_note=m_note-2000;
        m_fangdanyi=m_fangdanyi+1;

        if(m_note<0)
            {wxMessageBox(wxT("Music Note Is Not Enough!"));
            if (wxOK)
                {m_note=m_note+2000;
                fangdanyi->SetValue(0);
                }
            }
    }
    if(c==0)
    {
       m_note=m_note+2000;
        m_fangdanyi=m_fangdanyi-1;
    }
    this->Refresh(false);
}

void big_shopDialog::OnfeijiClick(wxCommandEvent& event)//������ѡ�����Ļ���5000��
{
    d=feiji->GetValue();
    if(d==1)
    {
        m_note=m_note-5000;
        m_lives=m_lives+1;

        if(m_note<0)
            {wxMessageBox(wxT("Music Note Is Not Enough!"));
            if (wxOK)
               {
                   m_note=m_note+5000;
                feiji->SetValue(0);

               }
            }
    }
    if(d==0)
    {
        m_note=m_note+5000;
        m_lives=m_lives-1;
    }
    this->Refresh(false);
}

void big_shopDialog::OnLeftUp(wxMouseEvent& event)//������̧��
{
   int x=event.GetX();
    int y=event.GetY();
    //if(event.Button(wxMOUSE_BTN_LEFT))
    if(x>=443&&x<=521&&y>=389&&y<=425)//��������cancel��������������ֵ�ָ�ԭֵ�����رմ���
    {
      //wxMessageBox(wxString::Format(_T("%d,%d"),x,y));
        m_note=old_m_note;
        m_zidan=old_m_zidan;
        m_lives=old_m_lives;
        m_zhadan=old_m_zhadan;
        m_fangdanyi=old_m_fangdanyi;
        this->Refresh(false);


        if ( IsModal() )
            EndModal(wxID_CANCEL);
    }
    if(x>=250&&x<=363&&y>=380&&y<=432)//��������OK�������������ı���ֵ����big_startDialog���ڣ�Ȼ��رմ���
    {
      //wxMessageBox(wxString::Format(_T("%d,%d"),x,y));
      m_call->SetZhuangbei(m_zidan,m_zhadan,m_fangdanyi,m_lives);//����SetZhuangbei������ֵ����big_startDialog����
        if ( IsModal() )
            EndModal(wxID_CANCEL);
    }
}


