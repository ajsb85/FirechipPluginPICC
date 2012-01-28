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
 
 // dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"

#include "PluginDefinition.h"
#include "resource.h"


extern FuncItem funcItem[nbFunc];
extern NppData nppData;
static HBITMAP hbmpToolbar;
static HICON hicoToolbar;
HINSTANCE hInst;

BOOL APIENTRY DllMain( HANDLE hModule, 
					  DWORD  reasonForCall, 
					  LPVOID lpReserved )
{
	switch (reasonForCall)
	{
	case DLL_PROCESS_ATTACH:
		pluginInit(hModule);
		hInst = (HINSTANCE) hModule;
			// To add button to toolbar
		hbmpToolbar = (HBITMAP)::LoadImage(hInst, MAKEINTRESOURCE(IDB_RUN_CCSC), IMAGE_BITMAP, 0, 0, (LR_DEFAULTSIZE | LR_LOADMAP3DCOLORS));
		hicoToolbar = (HICON)::LoadImage(hInst, MAKEINTRESOURCE(IDC_RUN_CCSC), IMAGE_ICON, 0, 0, LR_LOADMAP3DCOLORS | LR_LOADTRANSPARENT);
		break;

	case DLL_PROCESS_DETACH:
		commandMenuCleanUp();
		DeleteObject(hbmpToolbar);
		DeleteObject(hicoToolbar);
		pluginCleanUp();
		break;

	case DLL_THREAD_ATTACH:
		break;

	case DLL_THREAD_DETACH:
		break;
	}

	return TRUE;
}


extern "C" __declspec(dllexport) void setInfo(NppData notpadPlusData)
{
	nppData = notpadPlusData;
	commandMenuInit();
}

extern "C" __declspec(dllexport) const TCHAR * getName()
{
	return NPP_PLUGIN_NAME;
}

extern "C" __declspec(dllexport) FuncItem * getFuncsArray(int *nbF)
{
	*nbF = nbFunc;
	return funcItem;
}


extern "C" __declspec(dllexport) void beNotified(SCNotification *notifyCode)
{
	switch (notifyCode->nmhdr.code) 
	{
	case SCN_MODIFYATTEMPTRO:
		{
			//P4Edit(); 
		}
		break;
		case NPPN_TBMODIFICATION:
		{
			// Add the button to the toolbar
			toolbarIcons tbiFolder;
			tbiFolder.hToolbarBmp = hbmpToolbar;
			tbiFolder.hToolbarIcon = hicoToolbar;
			::SendMessage((HWND) notifyCode->nmhdr.hwndFrom, NPPM_ADDTOOLBARICON, (WPARAM) funcItem[0]._cmdID, (LPARAM) &tbiFolder);
			break;
		}
	}

}


// Here you can process the Npp Messages 
// I will make the messages accessible little by little, according to the need of plugin development.
// Please let me know if you need to access to some messages :
// http://sourceforge.net/forum/forum.php?forum_id=482781
//
extern "C" __declspec(dllexport) LRESULT messageProc(UINT Message, WPARAM wParam, LPARAM lParam)
{
	return TRUE;
}

#ifdef UNICODE
extern "C" __declspec(dllexport) BOOL isUnicode()
{
	return TRUE;
}
#endif //UNICODE

