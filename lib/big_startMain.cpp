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

BEGIN_EVENT_TABLE(big_startDialog,wxDialog)//�¼��б�
    //(*EventTable(big_startDialog)
    //*)
    EVT_PAINT(big_startDialog::OnPaint)
    EVT_ERASE_BACKGROUND(big_startDialog::OnEraseBackground)
END_EVENT_TABLE()



big_startDialog::big_startDialog(wxWindow* parent,wxWindowID id) //���캯��
{
    //(*Initialize(big_startDialog)
    Create(parent, id, _("Plane Shoot"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE|wxCLOSE_BOX, _T("id"));
    SetClientSize(wxSize(800,600));
    Move(wxPoint(-1,-1));
    Connect(wxEVT_MOTION,(wxObjectEventFunction)&big_startDialog::OnMouseMove);  //����ƶ���������
    Connect(wxEVT_LEFT_UP,(wxObjectEventFunction)&big_startDialog::OnLeftUp);//�������ɿ����������������
    //*)
    if(m_level==1) //��ʼ����Ϸ��������
        m_music=wxT("1.wav");

}

big_startDialog::~big_startDialog() // ��������
{
    //(*Destroy(big_startDialog)
    //*)
}

void big_startDialog::DrawTextString1(wxDC& dc, const wxString& text,wxCoord  x, wxCoord  y ) //�ڱ���ͼ��д��
{
wxFont font(10, wxFONTFAMILY_ROMAN, wxITALIC, wxBOLD);//�趨���塢��С
dc.SetFont(font);
dc.SetBackgroundMode(wxTRANSPARENT);
dc.SetTextForeground(*wxBLACK);//ǰ��ɫ
dc.SetTextBackground(*wxWHITE);//����ɫ
dc.DrawText(text, x,y);
}

void big_startDialog::OnPaint(wxPaintEvent& event)//��ͼ
{
wxBufferedPaintDC dc(this);//�����豸

PrepareDC(dc);

wxBitmap background(wxT("start.png"), wxBITMAP_TYPE_PNG);//�����ڱ���ͼ
dc.DrawBitmap(background, 0,0, true);
wxBitmap Start(wxT("T_start.png"), wxBITMAP_TYPE_PNG);//startͼ��
dc.DrawBitmap(Start, 330,240, true);
wxBitmap music(wxT("instruction.png"), wxBITMAP_TYPE_PNG);//˵��ͼ��
dc.DrawBitmap(music,200,370, true);
wxBitmap shop(wxT("shop.png"), wxBITMAP_TYPE_PNG);//�̵�ͼ��
dc.DrawBitmap(shop,-10,110, true);
wxBitmap model(wxT("model.png"), wxBITMAP_TYPE_PNG);//ģʽͼ��
dc.DrawBitmap(model,170,170, true);
wxBitmap points(wxT("points.png"), wxBITMAP_TYPE_PNG);//�ؿ�ͼ��
dc.DrawBitmap(points,295,158, true);

//DrawTextString1(dc,wxString::Format(wxT("Highest Scores:%2i"), m_mscore[m_level-1]),60,10);
//DrawTextString1(dc,wxString::Format(wxT("Level:%2i"), m_level),5,10);
DrawTextString1(dc,m_note,note_x,note_y);//����ƶ�������ͼ��ʱ��ʾ��ͼ�꺬��
}



void big_startDialog::OnEraseBackground(wxEraseEvent& event)
{
}

void big_startDialog::SetModel(wxString model)//����ģʽ
{
    m_model=model;//ʹ�õ�ǰ�ؿ��봫��ؿ���ͬ
}

void big_startDialog::SetScore(int mscore)//������߷�
{
    m_mscore[m_level-1]=mscore;//ʹ�õ�ǰ��߷��봫����߷���ͬ

}


void big_startDialog::SetZhuangbei(int zidan,int zhadan,int fangdanyi,int lives)//����˫���ӵ���ը���������¡����ĸ�����ʹ���봫��ֵ��ͬ
{
    m_zidan=zidan;
    m_zhadan=zhadan;
    m_fangdanyi=fangdanyi;
    m_lives=lives;

}

void big_startDialog::SetLevel(int level)//���ùؿ���ʹ���봫��ֵ��ͬ
{
    m_level=level;

}

void big_startDialog::SetMusic(wxString music)//���ñ������֣�ʹ���봫��ֵ��ͬ
{
    m_music=music;

}

void big_startDialog::OnInit(wxInitDialogEvent& event)
{

}



void big_startDialog::OnMouseMove(wxMouseEvent& event)//����ƶ�����
{
    int x=event.GetX();//��õ�ǰ���λ�õ�xֵ
    int y=event.GetY();//��õ�ǰ���λ�õ�yֵ
    m_note=wxT(" ");
    note_x=1000;
    note_y=1000;//��ʼ��m_note�ǿ��ַ�����������(1000,1000)
    bool a;
    a=(x>=343&&x<=456&&y>=249&&y<=280)||(x>=200&&x<=245&&y>=364&&y<=420)||(x>=312&&x<=358&&y>=379&&y<=420)||(x>=407&&x<=464&&y>=372&&y<=428)||(x>=518&&x<=570&&y>=380&&y<=427);

    if(x>=343&&x<=456&&y>=249&&y<=280)//�������ڸ÷�Χ�ڣ�start�ϣ����ͼ�����С��
    {
        this->SetCursor(wxImage("cursor.png"));
    }
    if(x>=200&&x<=245&&y>=364&&y<=420)//�������ڸ÷�Χ�ڣ�˵��ͼ���ϣ����ͼ�����С�֣������Ա���ʾInstruction����
    {
        m_note=wxT("Instruction");
        note_x=245;
        note_y=364;
        this->SetCursor(wxImage("cursor.png"));
    }

    if(x>=312&&x<=358&&y>=379&&y<=420)//�������ڸ÷�Χ�ڣ��̵�ͼ���ϣ����ͼ�����С�֣������Ա���ʾShop����
    {
        m_note=wxT("Shop");
        note_x=358;
        note_y=365;
        this->SetCursor(wxImage("cursor.png"));
    }

    if(x>=407&&x<=464&&y>=372&&y<=428)//�������ڸ÷�Χ�ڣ�ģʽͼ���ϣ����ͼ�����С�֣������Ա���ʾModel����
    {
        m_note=wxT("Model");
        note_x=464;
        note_y=372;
        this->SetCursor(wxImage("cursor.png"));
    }

    if(x>=518&&x<=570&&y>=380&&y<=427)//�������ڸ÷�Χ�ڣ��ؿ�ͼ���ϣ����ͼ�����С�֣������Ա���ʾLevel����
    {
        m_note=wxT("Level");
        note_x=550;
        note_y=360;
        this->SetCursor(wxImage("cursor.png"));
    }

    if(!a)//�����겻�����Ϸ�Χ�����ͼ����ɼ�ͷ��ע�͵������Ƶ�Զ��
    {
        m_note=wxT(" ");
        note_x=1000;
        note_y=1000;
        this->SetCursor(wxImage("mouse.png"));
    }
this->Refresh();//������϶�����ˢ�´���
    //if(event.ButtonUp(wxMOUSE_BTN_LEFT))
      //  wxMessageBox(wxString::Format(_T("%d,%d"),x,y));

}

void big_startDialog::OnLeftUp(wxMouseEvent& event)//������̧����
{
   int x=event.GetX();
    int y=event.GetY();//�Ȼ�����λ��
    //if(event.Button(wxMOUSE_BTN_LEFT))

  if(x>=343&&x<=456&&y>=249&&y<=280)    //��Start������
    {
    big_start1Dialog *startdialog=new big_start1Dialog(this);//����һ���µ���Ϸ����
    startdialog->SetModel(m_model);//����SetModel����������ģʽ��ʹ�´��ڵ�ָ��ָ���ֵ
    startdialog->SetLevel(m_level);//����SetLevel���������ùؿ���ʹ�´��ڵ�ָ��ָ���ֵ
    startdialog->SetMusic(m_music);//����SetMusic���������ñ������֣�ʹ�´��ڵ�ָ��ָ���ֵ
    startdialog->SetZhuangbei(m_zidan,m_zhadan,m_fangdanyi,m_lives);//����SethZuangbei����������˫���ӵ���ը���������¡�������ʹ�´��ڵ�ָ��ָ���ֵ
    m_mscore[m_level-1]=startdialog->Getscore();
    wxSound::Play(m_music, wxSOUND_ASYNC|wxSOUND_LOOP);//���ű�������
       startdialog->ShowModal();//����ģ̬����Ϸ����
       }

  if(x>=200&&x<=245&&y>=364&&y<=420)   //��˵��ͼ����
   {
       big_musicDialog *musicdialog=new big_musicDialog(this);//����һ���µ�˵������
       musicdialog->ShowModal();//ģ̬����ʾ����
    }



  if(x>=312&&x<=358&&y>=379&&y<=420)   //���̵�ͼ����
    {
       big_shopDialog *shopdialog=new big_shopDialog(this);//����һ���µ��̵괰��
       shopdialog->SetCall(this);//���ô��ڵ����̵���洫��Ĺ����̵��ֵ������Ϸ����
       shopdialog->ShowModal();//��ģ̬������
    }

  if(x>=407&&x<=464&&y>=372&&y<=428)  //��ģʽͼ����
    {
       big_modelDialog *modeldialog=new big_modelDialog(this);//����һ���µ�ģʽ����
       modeldialog->SetCall(this);//���ô��ڵ���ģʽ���洫��Ĺ���ģʽ��ֵ������Ϸ����
       modeldialog->ShowModal();
    }

  if(x>=518&&x<=570&&y>=380&&y<=427)
    {
       big_pointsDialog *pointsdialog=new big_pointsDialog(this);//����һ���µĹؿ�����
       pointsdialog->SetCall(this);//���ô��ڵ��ɹؿ����洫��Ĺ��ڹؿ���ֵ������Ϸ����
      // pointsdialog->SetScore(m_mscore[m_level-1]);
       pointsdialog->ShowModal();
    }

}

