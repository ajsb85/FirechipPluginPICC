/* 
<Firechip� IDE: Is a free (GNU) source code editor for electronics designer.>
 Copyright � 2012 "Alexander Salas" <alexander@firechip.info>

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


#ifndef DOCKING_H
#define DOCKING_H


#include "windows.h"

//   defines for docking manager
#define	CONT_LEFT		0
#define	CONT_RIGHT		1
#define	CONT_TOP		2
#define	CONT_BOTTOM		3
#define	DOCKCONT_MAX	4

// mask params for plugins of internal dialogs
#define DWS_ICONTAB			0x00000001			// Icon for tabs are available
#define DWS_ICONBAR			0x00000002			// Icon for icon bar are available (currently not supported)
#define DWS_ADDINFO			0x00000004			// Additional information are in use
#define DWS_PARAMSALL		(DWS_ICONTAB|DWS_ICONBAR|DWS_ADDINFO)

// default docking values for first call of plugin
#define DWS_DF_CONT_LEFT	(CONT_LEFT	<< 28)	// default docking on left
#define DWS_DF_CONT_RIGHT	(CONT_RIGHT	<< 28)	// default docking on right
#define DWS_DF_CONT_TOP		(CONT_TOP	<< 28)	// default docking on top
#define DWS_DF_CONT_BOTTOM	(CONT_BOTTOM << 28)	// default docking on bottom
#define DWS_DF_FLOATING		0x80000000			// default state is floating


typedef struct {
	HWND		hClient;		// client Window Handle
	LPTSTR		pszName;		// name of plugin (shown in window)
	int			dlgID;			// a funcItem provides the function pointer to start a dialog. Please parse here these ID

	/* user modifications */
	UINT		uMask;			// mask params: look to above defines
	HICON		hIconTab;		// icon for tabs
	LPTSTR		pszAddInfo;		// for plugin to display additional informations

	/* internal data, do not use !!! */
	RECT		rcFloat;		// floating position
	int			iPrevCont;		// stores the privious container (toggling between float and dock)
	LPCTSTR		pszModuleName;	// it's the plugin file name. It's used to identify the plugin
} tTbData;



/* notifications of docking */
#define DMN_FIRST 1050
	#define DMN_CLOSE					(DMN_FIRST + 1)
	//nmhdr.code = DWORD(DMN_CLOSE, 0));
	//nmhdr.hwndFrom = hwndNpp;
	//nmhdr.idFrom = ctrlIdNpp;

	#define DMN_DOCK		            (DMN_FIRST + 2)
    #define DMN_FLOAT					(DMN_FIRST + 3)
	//nmhdr.code = DWORD(DMN_XXX, int newContainer);
	//nmhdr.hwndFrom = hwndNpp;
	//nmhdr.idFrom = ctrlIdNpp;



#endif // DOCKING_H
