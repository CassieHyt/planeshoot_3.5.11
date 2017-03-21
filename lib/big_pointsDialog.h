#ifndef BIG_POINTSDIALOG_H
#define BIG_POINTSDIALOG_H
#include <wx/dcbuffer.h>
#include "big_startMain.h"

//(*Headers(big_pointsDialog)
#include <wx/dialog.h>
//*)

struct object1//定义结构体存坐标
{
    int x1;
    int y1;
} ;


class big_startDialog;
class big_pointsDialog: public wxDialog
{
	public:

		big_pointsDialog(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~big_pointsDialog();
		void PaintBackground(wxDC& dc);
        void OnEraseBackground(wxEraseEvent& event);
        int m_level;//关卡
        wxString m_music;//背景音乐名
        void SetCall(big_startDialog * call){m_call=call;}
        void SetScore(int mscore);//设置最高分
		//(*Declarations(big_pointsDialog)
		//*)

	protected:

		//(*Identifiers(big_pointsDialog)
		//*)

	private:

		//(*Handlers(big_pointsDialog)
		//*)
		void OnQuit(wxCommandEvent& event);
		void OnMouseMove(wxMouseEvent& event);
        void OnLeftUp(wxMouseEvent& event);
		void OnPaint(wxPaintEvent& event);
		struct object1 m_lock[7];//锁结构体，记录每个锁的坐标
		void Init();
		void DrawText(const wxString& text,wxCoord x, wxCoord y);
		void DrawT();
		int m_mscore[10];
		big_startDialog * m_call;//定义big_startDialog类型的指针变量

		DECLARE_EVENT_TABLE()
};

#endif
