/***************************************************************
 * Name:      big_startMain.h
 * Purpose:   Defines Application Frame
 * Author:    zyq ()
 * Created:   2014-05-12
 * Copyright: zyq ()
 * License:
 **************************************************************/

#ifndef BIG_STARTMAIN_H
#define BIG_STARTMAIN_H
#include <wx/dcclient.h>
#include <wx/bitmap.h>
#include <wx/dcbuffer.h>
#include <wx/scrolwin.h>
#include <wx/chartype.h>
#include <wx/mediactrl.h>
#include "big_musicDialog.h"
#include "big_shopDialog.h"
#include "big_modelDialog.h"
#include "big_pointsDialog.h"
#include "big_start1Main.h"


//(*Headers(big_startDialog)
#include <wx/dialog.h>
//*)


class big_modelDialog;
class big_shopDialog;
class big_pointsDialog;
class big_startDialog: public wxDialog//����̳�wxDialog���big_startDialog��
{
    public:
        big_startDialog(wxWindow* parent,wxWindowID id = -1);//���캯��
        /*myBitmapButton(wxWindow* parent,wxWindowID id = -1, const wxBitmap &bitmap,
                       const wxPoint &pos,const wxString &  name)*/
        virtual ~big_startDialog();
                void PaintBackground(wxDC& dc);//���Ʊ���
        void OnEraseBackground(wxEraseEvent& event);
        void SetModel(wxString model);//����ģʽ
        void SetLevel(int level);//���ùؿ�
        void SetMusic(wxString music);//���ñ�������
        void SetZhuangbei(int zidan,int zhadan,int fangdanyi,int lives);//����˫���ӵ���ը���������¡���
        void SetScore(int mscore);//������߷�
    private:

        //(*Handlers(big_startDialog)
        void OnInit(wxInitDialogEvent& event);
        void OnMouseMove(wxMouseEvent& event);//����¼�������ƶ��ķ���
        void OnLeftUp(wxMouseEvent& event);//����¼���������̧�𷽷�
        //*)

        //(*Identifiers(big_startDialog)
        //*)

        //(*Declarations(big_startDialog)
        //*)
        void DrawText(const wxString& text,wxCoord x, wxCoord y);
		void DrawTextString1(wxDC& dc, const wxString& text,int x,int y);
        void OnPaint(wxPaintEvent& event);
        void DrawTextString(wxDC& dc, const wxString& text,int x,int y);//�ڱ���ͼ��д��
        //wxDialog *musicdialog;
        //wxDialog *shopdialog;
        wxString m_model;//ģʽ
        int m_zidan;//˫���ӵ�
        int m_zhadan;//ը��
        int m_fangdanyi;//������
        int m_lives;//��
        int m_level;//�ؿ�
        int m_mscore[10];//��¼ÿ����߷�
        int note_x;//ע�͵�����
        int note_y;
        wxString m_note;//ע�͵��ַ���
        wxString m_music;//�����������ֵ��ַ���

        DECLARE_EVENT_TABLE()
};



#endif // BIG_STARTMAIN_H
