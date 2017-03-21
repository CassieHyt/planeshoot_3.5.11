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

struct object//定义结构体存坐标
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
        big_startDialog * m_call;//定义big_startDialog类型的指针
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

        struct object m_player;//定义玩家飞机结构体
        struct object m_ball;//定义爆炸效果图结构体
        struct object m_ballet[20];//定义子弹结构体
        struct object m_enemies[20];//定义普通敌机结构体
        struct object m_enemies2[5];//定义特殊敌机结构体
        bool m_gameover;
        int m_lives;
        int i,j,m;
        void draw(wxDC &dc);
        void DrawTextString(wxDC& dc, const wxString& text,int x,int y);
        int Crash(int x1,int x2,int y1,int y2);//普通敌机被打中
        int Crash2(int x1,int x2,int y1,int y2);//特殊敌机被打中
        int Crashdouble(int x1,int x2,int y1,int y2);//敌机被双排子弹打中
        int Crashme(int x1,int x2,int y1,int y2);//玩家飞机被普通敌机撞毁
        int Crashme2(int x1,int x2,int y1,int y2);//玩家飞机被特殊敌机撞毁
        void explode();
        wxTimer m_timer;
        int m_i;
        int m_j;
        int m_m[20];
        int m_m2[5];
        int m_e[20];
        int m_e2[5];
        int m_score[10];//分数
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
