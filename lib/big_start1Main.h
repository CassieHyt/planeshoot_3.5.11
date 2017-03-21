/***************************************************************
 * Name:      big_start1Main.h
 * Purpose:   Defines Application Frame
 * Author:    zyq ()
 * Created:   2014-05-12
 * Copyright: zyq ()
 * License:
 **************************************************************/

#ifndef BIG_START1MAIN_H
#define BIG_START1MAIN_H
#include <wx/dcclient.h>
#include <wx/bitmap.h>
#include <wx/dcbuffer.h>
#include <wx/scrolwin.h>
#include <wx/chartype.h>
#include <wx/log.h>
#include <wx/timer.h>
#include "wx/glcanvas.h"
#include <wx/graphics.h>
#include <wx/dialog.h>
//#include "big_pointsDialog.h"
//extern int m_level;
//(*Headers(big_startDialog)
#include <wx/dialog.h>
//*)

struct object//����ṹ�������
{
    int x, y;
};
class big_startDialog;
class big_start1Dialog: public wxDialog
{
    public:
        big_start1Dialog(wxWindow* parent,wxWindowID id = -1);
        void Ontimer(wxTimerEvent& event);
        virtual ~big_start1Dialog();

        void SetModel(wxString model);
        void SetZhuangbei(int zidan,int zhadan,int fangdanyi,int lives);
        void SetLevel(int level);
        void SetMusic(wxString music);
        void SetCall(big_startDialog * call){m_call=call;}
        void SetScore(int mscore);
        int Getscore();
        big_startDialog * m_call;//����big_startDialog���͵�ָ��
    private:
        //(*Handlers(big_startDialog)

        void OnAbout(wxCommandEvent& event);
        void OnBitmapButton1Click(wxCommandEvent& event);
        //*)

        //(*Identifiers(big_startDialog)
        //*)

        //(*Declarations(big_startDialog)
        //*)
        void OnQuit(wxCloseEvent& event);
        void OnPaint(wxPaintEvent& event);
        void OnKeyDown(wxKeyEvent& event);
        void PaintBackground(wxDC& dc);
        void OnEraseBackground(wxEraseEvent& event);

        void ResetObjects();
        void Init();

        struct object m_player;//������ҷɻ��ṹ��
        struct object m_ball;//���屬ըЧ��ͼ�ṹ��
        struct object m_ballet[20];//�����ӵ��ṹ��
        struct object m_enemies[20];//������ͨ�л��ṹ��
        struct object m_enemies2[5];//��������л��ṹ��
        bool m_gameover;
        int m_lives;
        int i,j,m;
        void draw(wxDC &dc);
        void DrawTextString(wxDC& dc, const wxString& text,int x,int y);
        int Crash(int x1,int x2,int y1,int y2);//��ͨ�л�������
        int Crash2(int x1,int x2,int y1,int y2);//����л�������
        int Crashdouble(int x1,int x2,int y1,int y2);//�л���˫���ӵ�����
        int Crashme(int x1,int x2,int y1,int y2);//��ҷɻ�����ͨ�л�ײ��
        int Crashme2(int x1,int x2,int y1,int y2);//��ҷɻ�������л�ײ��
        void explode();
        wxTimer m_timer;
        int m_i;
        int m_j;
        int m_m[20];
        int m_m2[5];
        int m_e[20];
        int m_e2[5];
        int m_score[10];//����
        bool let1,let2,let3;
        int m_level;
        int m_mscore[10];
        int m_zidan;
        int m_zhadan;
        int m_fangdanyi;
         int mycount;

        wxString m_model;
        wxString balle;
        wxString m_plane;
        wxString m_music;
        DECLARE_EVENT_TABLE()
};

#endif // BIG_STARTMAIN_H
