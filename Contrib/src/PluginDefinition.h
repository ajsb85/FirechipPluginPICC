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

#ifndef PLUGINDEFINITION_H
#define PLUGINDEFINITION_H

//
// All difinitions of plugin interface
//
#include <string>       // For alertString()
#include <vector>
#include <tchar.h>      // For _tcscpy, _tcscat 
#include <fstream>      // For file reading and writing
#include <winhttp.h>    // For http requests, Add winhttp.lib to additional dependencies if there is external definition error
#include <process.h>    // For thread
#include <regex>
#include <algorithm>
#include <shlobj.h>
#include <shlwapi.h>
#include <shellapi.h>
#include <stdlib.h>
#include <string>
#include <iostream>

#include "PluginInterface.h"

//-------------------------------------//
//-- STEP 1. DEFINE YOUR PLUGIN NAME --//
//-------------------------------------//
// Here define your plugin name
//
const TCHAR NPP_PLUGIN_NAME[] = TEXT("CCS C Compiler");

//-----------------------------------------------//
//-- STEP 2. DEFINE YOUR PLUGIN COMMAND NUMBER --//
//-----------------------------------------------//
//
// Here define the number of your plugin commands
//
const int nbFunc = 17;


//
// Initialization of your plugin data
// It will be called while plugin loading
//
void pluginInit(HANDLE hModule);

//
// Cleaning of your plugin
// It will be called while plugin unloading
//
void pluginCleanUp();

//
//Initialization of your plugin commands
//
void commandMenuInit();

//
//Clean up your plugin commands allocation (if any)
//
void commandMenuCleanUp();

//
// Function which sets your command 
//
bool setCommand(size_t index, TCHAR *cmdName, PFUNCPLUGINCMD pFunc, ShortcutKey *sk = NULL, bool check0nInit = false);


//
// Your plugin command functions
//

void piccCompile();
void buildProject();
void buildOptionsDlg();
void compilerVersion();
void supportedDevices();
void deviceTableEditor();
void docGenerator();
void signalGenerator();
void numConvert();
void coffDump();
void pcbWizard();
void pcdWizard();
void pcbHelp();
void pcdHelp();

#endif //PLUGINDEFINITION_H
