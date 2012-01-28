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
 
#include "ImageListSet.h"
//#include "resource.h"

void ToolBarIcons::init(ToolBarButtonUnit *buttonUnitArray, int arraySize)
{
	for (int i = 0 ; i < arraySize ; i++)
		_tbiis.push_back(buttonUnitArray[i]);
	_nbCmd = arraySize;
}

void ToolBarIcons::create(HINSTANCE hInst, int iconSize)
{
	_iconListVector.push_back(IconList());
	_iconListVector.push_back(IconList());
	_iconListVector.push_back(IconList());
	//_iconListVector.push_back(IconList());

	_iconListVector[HLIST_DEFAULT].create(hInst, iconSize);
	_iconListVector[HLIST_HOT].create(hInst, iconSize);
	_iconListVector[HLIST_DISABLE].create(hInst, iconSize);
	//_iconListVector[HLIST_UGLY].create(hInst, 16);

	reInit(iconSize);
}

void ToolBarIcons::destroy()
{
	_iconListVector[HLIST_DEFAULT].destroy();
	_iconListVector[HLIST_HOT].destroy();
	_iconListVector[HLIST_DISABLE].destroy();
	//_iconListVector[HLIST_UGLY].destroy();
}


