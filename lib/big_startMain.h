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
class big_startDialog: public wxDialog//定义继承wxDialog类的big_startDialog类
{
    public:
        big_startDialog(wxWindow* parent,wxWindowID id = -1);//构造函数
        /*myBitmapButton(wxWindow* parent,wxWindowID id = -1, const wxBitmap &bitmap,
                       const wxPoint &pos,const wxString &  name)*/
        virtual ~big_startDialog();
                void PaintBackground(wxDC& dc);//绘制背景
        void OnEraseBackground(wxEraseEvent& event);
        void SetModel(wxString model);//设置模式
        void SetLevel(int level);//设置关卡
        void SetMusic(wxString music);//设置背景音乐
        void SetZhuangbei(int zidan,int zhadan,int fangdanyi,int lives);//设置双排子弹、炸弹、防弹衣、命
        void SetScore(int mscore);//设置最高分
    private:

        //(*Handlers(big_startDialog)
        void OnInit(wxInitDialogEvent& event);
        void OnMouseMove(wxMouseEvent& event);//鼠标事件的鼠标移动的方法
        void OnLeftUp(wxMouseEvent& event);//鼠标事件的鼠标左键抬起方法
        //*)

        //(*Identifiers(big_startDialog)
        //*)

        //(*Declarations(big_startDialog)
        //*)
        void DrawText(const wxString& text,wxCoord x, wxCoord y);
		void DrawTextString1(wxDC& dc, const wxString& text,int x,int y);
        void OnPaint(wxPaintEvent& event);
        void DrawTextString(wxDC& dc, const wxString& text,int x,int y);//在背景图上写字
        //wxDialog *musicdialog;
        //wxDialog *shopdialog;
        wxString m_model;//模式
        int m_zidan;//双排子弹
        int m_zhadan;//炸弹
        int m_fangdanyi;//防弹衣
        int m_lives;//命
        int m_level;//关卡
        int m_mscore[10];//记录每关最高分
        int note_x;//注释的坐标
        int note_y;
        wxString m_note;//注释的字符串
        wxString m_music;//背景音乐名字的字符串

        DECLARE_EVENT_TABLE()
};



#endif // BIG_STARTMAIN_H
