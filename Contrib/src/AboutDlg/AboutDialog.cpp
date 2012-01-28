/* 
<Firechip™ IDE: Is a free (GNU) source code editor for electronics designer.>
 Copyright © 2012 "Alexander Salas" <alexander@firechip.info>

 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by 
 the Free Software Foundation, either version 3 of the License, or
 any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program. If not, see <http://www.gnu.org/licenses/>.*/
 
#include "precompiled_headers.h"
#include "AboutDialog.h"
#include "PluginInterface.h"
#include "resource1.h"

void AboutDialog::doDialog()
{
    if (!isCreated())
        create(IDD_ABOUT_DLG);

	goToCenter();
}


BOOL CALLBACK AboutDialog::run_dlgProc(HWND /*hWnd*/, UINT Message, WPARAM wParam, LPARAM /*lParam*/)
{
	switch (Message) 
	{
        case WM_INITDIALOG :
		{
           
			return TRUE;
		}
		case WM_COMMAND : 
		{
			switch (wParam)
			{
				case IDOK :
				case IDCANCEL :
					display(FALSE);
					return TRUE;

				default :
					break;
			}
		}
	}
	return FALSE;
}

