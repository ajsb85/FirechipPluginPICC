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
 
#ifndef NPPAPIUTILS_H
#define NPPAPIUTILS_H

#include "PluginDefinition.h"

// Connecting to Scintilla
HWND getCurrentScintilla(int which = -1);
sptr_t SendScintilla(unsigned int iMessage, uptr_t wParam, sptr_t lParam);
void updateScintilla(int which = -1,HWND curScintilla = NULL);
// Setting the menu
ShortcutKey* setShortCutKey(bool _isAlt, bool _isCtrl, bool _isShift, UCHAR _key);
int setCommand(TCHAR *cmdName = TEXT(""), PFUNCPLUGINCMD pFunc = NULL, ShortcutKey *sk = NULL, bool check0nInit = false);

// Show messageboxes
int showMessageBox(TCHAR* text = TEXT(""), int flags = MB_OK);

// Search in Scintilla
int searchNext(char* searchText, bool regExp = false);
int searchPrev(char* searchText, bool regExp = false);

// Getting Text from Scintilla
unsigned int sciGetText(char **text, int start = -1, int end = -1);
//unsigned int sciGetText(HWND hwnd, char **text, int start, int end)

void closeTab(TCHAR* path);
void openTab(TCHAR* path);
void emptyFile(TCHAR* fileName);

#endif //NPPAPIUTILS_H