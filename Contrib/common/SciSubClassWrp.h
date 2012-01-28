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

#ifndef SCI_SUB_CLASS_WRP_H
#define SCI_SUB_CLASS_WRP_H

#include "Scintilla.h"


class SciSubClassWrp
{
public:
	HWND hWnd;

	SciSubClassWrp()
		:
		hWnd(0)
		,SciCallWndProc(0)
		,SciFunc(0)
		,SciPtr(0)
		,OrigSciWndProc(0)
	{}

	void Init( HWND hSci, WNDPROC NewWndProc )
	{
		hWnd = hSci;
		SubclassScintillaWndProc( NewWndProc );
		SciFunc = (int(*)(void*,int,int,int))::SendMessage( hSci, SCI_GETDIRECTFUNCTION, 0, 0);
		SciPtr = (void*)::SendMessage( hSci, SCI_GETDIRECTPOINTER, 0, 0);
	}

	void CleanUp()
	{
		if (OrigSciWndProc != 0)
		{
			if ( ::IsWindowUnicode( hWnd ) )
			{
				SetWindowLongW( hWnd, GWL_WNDPROC, (LONG) OrigSciWndProc );
			}
			else
			{
				SetWindowLongA( hWnd, GWL_WNDPROC, (LONG) OrigSciWndProc );
			}
		}
		OrigSciWndProc = 0;
	}

	LRESULT execute(UINT Msg, WPARAM wParam=0, LPARAM lParam=0) const
	{
		return SciFunc(SciPtr, static_cast<int>(Msg), static_cast<int>(wParam), static_cast<int>(lParam));
	};

	LRESULT CALLBACK CallScintillaWndProc( HWND hwnd, UINT msg, WPARAM wp, LPARAM lp )
	{
		return SciCallWndProc( OrigSciWndProc, hwnd, msg, wp, lp );
	}

private:
	LRESULT (WINAPI *SciCallWndProc) (WNDPROC,HWND,UINT,WPARAM,LPARAM);
	int (* SciFunc) (void*, int, int, int);
	void * SciPtr;
	WNDPROC OrigSciWndProc;

	void SubclassScintillaWndProc( WNDPROC NewWndProc )
	{
		if ( ::IsWindowUnicode( hWnd ) )
		{
			SciCallWndProc = CallWindowProcW;
			OrigSciWndProc = (WNDPROC) SetWindowLongW( hWnd, GWL_WNDPROC, (LONG) NewWndProc );
		}
		else
		{
			SciCallWndProc = CallWindowProcA;
			OrigSciWndProc = (WNDPROC) SetWindowLongA( hWnd, GWL_WNDPROC, (LONG) NewWndProc );
		}
	}
};

#endif
