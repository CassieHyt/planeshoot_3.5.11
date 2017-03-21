#ifndef BIG_MODELDIALOG_H
#define BIG_MODELDIALOG_H
#include <wx/dcbuffer.h>
#include "big_startMain.h"

//(*Headers(big_modelDialog)
#include <wx/dialog.h>
//*)
class big_startDialog;
class big_modelDialog: public wxDialog
{
	public:

		big_modelDialog(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);//���캯��
		virtual ~big_modelDialog();
		void PaintBackground(wxDC& dc);
        void OnEraseBackground(wxEraseEvent& event);
        wxString m_model;//ģʽ
        void SetCall(big_startDialog * call){m_call=call;}//���ƴ���ֵ
		//(*Declarations(big_modelDialog)
		//*)

	protected:

		//(*Identifiers(big_modelDialog)
		//*)

	private:

		//(*Handlers(big_modelDialog)
		//*)
		void OnQuit(wxCommandEvent& event);
		void OnMouseMove(wxMouseEvent& event);
        void OnLeftUp(wxMouseEvent& event);
		void OnPaint(wxPaintEvent& event);

		//int mn;
		void DrawText(const wxString& text,wxCoord x, wxCoord y);
        big_startDialog * m_call;//����big_startDialog����ָ�����

		DECLARE_EVENT_TABLE()
};

#endif
