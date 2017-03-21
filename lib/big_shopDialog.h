#ifndef BIG_SHOPDIALOG_H
#define BIG_SHOPDIALOG_H
#include <wx/dcbuffer.h>
#include "big_startMain.h"

//(*Headers(big_shopDialog)
#include <wx/checkbox.h>
#include <wx/gbsizer.h>
#include <wx/dialog.h>
//*)


class big_startDialog;
class big_shopDialog: public wxDialog
{
	public:

		big_shopDialog(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~big_shopDialog();
		void PaintBackground(wxDC& dc);
        void OnEraseBackground(wxEraseEvent& event);
        int m_zidan;//双排子弹
        int m_zhadan;//炸弹
        int m_fangdanyi;//防弹衣
        int m_lives;//生命
        void SetCall(big_startDialog * call){m_call=call;}

		//(*Declarations(big_shopDialog)
		wxCheckBox* fangdanyi;
		wxCheckBox* zhadan;
		wxCheckBox* zidan;
		wxCheckBox* feiji;
		//*)


	protected:

		//(*Identifiers(big_shopDialog)
		static const long ID_CHECKBOX1;
		static const long ID_CHECKBOX2;
		static const long ID_CHECKBOX4;
		static const long ID_CHECKBOX3;
		//*)


	private:

		//(*Handlers(big_shopDialog)
		void OnCheckBox1Click(wxCommandEvent& event);
		void OnCheckBox1Click1(wxCommandEvent& event);
		void OnzhadanClick(wxCommandEvent& event);
		void OnfangdanyiClick(wxCommandEvent& event);
		void OnfeijiClick(wxCommandEvent& event);
		//*)
		void Init();
		void OnQuit(wxCommandEvent& event);
		void OnMouseMove(wxMouseEvent& event);
        void OnLeftUp(wxMouseEvent& event);
		void OnPaint(wxPaintEvent& event);
		void DrawText(const wxString& text,wxCoord x, wxCoord y);
		void DrawTextString(wxDC& dc, const wxString& text,int x,int y);
		int m_note=10000;
		int old_m_note;
		int new_m_note;
		//int m_zidan;
		//int m_zhadan;
		//int m_fangdanyi;
		//int m_lives;
		int old_m_zhadan;//原炸弹数
		int new_m_zhadan;
		int old_m_fangdanyi;//原防弹衣数
		int new_m_fangdanyi;
		int old_m_lives;//原生命数
		int new_m_lives;
		int old_m_zidan;//原双排子弹数
		int new_m_zidan;
		int a;
		int b;
		int c;
		int d;
		void DrawT();
		big_startDialog * m_call;
		DECLARE_EVENT_TABLE()
};

#endif
