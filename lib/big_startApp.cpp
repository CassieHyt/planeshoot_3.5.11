/***************************************************************
 * Name:      big_startApp.cpp
 * Purpose:   Code for Application Class
 * Author:    zyq ()
 * Created:   2014-05-12
 * Copyright: zyq ()
 * License:
 **************************************************************/

#include "big_startApp.h"

//(*AppHeaders
#include "big_startMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(big_startApp);

bool big_startApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	big_startDialog Dlg(0);
    	SetTopWindow(&Dlg);
    	Dlg.ShowModal();
    	wxsOK = false;
    }
    //*)
    return wxsOK;

}
