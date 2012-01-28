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

#ifndef STATIC_DIALOG_H
#define STATIC_DIALOG_H

//#include "resource.h"
#include "Window.h"
#include <TCHAR.h>
#include "notepad_plus_msgs.h"

#include <uxtheme.h>

typedef HRESULT (WINAPI * ETDTProc) (HWND, DWORD);

enum PosAlign{ALIGNPOS_LEFT, ALIGNPOS_RIGHT, ALIGNPOS_TOP, ALIGNPOS_BOTTOM};

struct DLGTEMPLATEEX {
      WORD   dlgVer;
      WORD   signature;
      DWORD  helpID;
      DWORD  exStyle;
      DWORD  style; 
      WORD   cDlgItems;
      short  x;
      short  y;    
      short  cx;
      short  cy;
      // The structure has more fields but are variable length
} ;

class StaticDialog : public Window
{
public :
	StaticDialog() : Window(), _isModeles(false) {};
	~StaticDialog(){
		if (isCreated())
			destroy();
	};
	virtual void create(int dialogID, bool isRTL = false, bool isModeles = true);

    virtual bool isCreated() const {
		return (_hSelf != NULL);
	};

	void goToCenter();

	void display(bool toShow = true) const;

	POINT getLeftTopPoint(HWND hwnd/*, POINT & p*/) const {
		RECT rc;
		::GetWindowRect(hwnd, &rc);
		POINT p;
		p.x = rc.left;
		p.y = rc.top;
		::ScreenToClient(_hSelf, &p);
		return p;
	};

    void destroy() {
		if (_isModeles) {
			::SendMessage(_hParent, NPPM_MODELESSDIALOG, MODELESSDIALOGREMOVE, (WPARAM)_hSelf);
		}
		::DestroyWindow(_hSelf);
	};

protected :
	RECT _rc;
	static BOOL CALLBACK dlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
	virtual BOOL CALLBACK run_dlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) = 0;

    void alignWith(HWND handle, HWND handle2Align, PosAlign pos, POINT & point);
	HGLOBAL makeRTLResource(int dialogID, DLGTEMPLATE **ppMyDlgTemplate);

	bool		_isModeles;
};

#endif //STATIC_DIALOG_H
