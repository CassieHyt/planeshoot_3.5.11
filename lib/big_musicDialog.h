#ifndef BIG_MUSICDIALOG_H
#define BIG_MUSICDIALOG_H
#include <wx/dcbuffer.h>
#include <wx/mediactrl.h>
//(*Headers(big_musicDialog)
#include <wx/dialog.h>
//*)

class big_musicDialog: public wxDialog
{
	public:

		big_musicDialog(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);//构造函数
		virtual ~big_musicDialog();
		void PaintBackground(wxDC& dc);
        void OnEraseBackground(wxEraseEvent& event);

		//(*Declarations(big_musicDialog)
		//*)

	protected:

		//(*Identifiers(big_musicDialog)
		//*)

	private:

		//(*Handlers(big_musicDialog)
		//*)
		void OnQuit(wxCommandEvent& event);
		void OnMouseMove(wxMouseEvent& event);//鼠标移动方法
        void OnLeftUp(wxMouseEvent& event);//鼠标左键抬起方法
		void OnPaint(wxPaintEvent& event);
		//void OnPlay(wxMediaEvent& event);
        //wxMediaCtrl* m_music;


		DECLARE_EVENT_TABLE()
};

#endif
