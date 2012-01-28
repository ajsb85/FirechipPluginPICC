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
 
#include "stdafx.h"

#include "PluginDefinition.h"
#include "FirechipPluginVersion.h"
#include "menuCmdID.h"
#include "icon_error_16.h"
#include "icon_warning_16.h"
//
// The plugin data that Notepad++ needs
//
FuncItem funcItem[nbFunc];

//
// The data of Notepad++ that you can use in your plugin commands
//
NppData nppData;


//
// Initialize your plugin data here
// It will be called while plugin loading   
    
void pluginInit(HANDLE hModule)
{
}


//
// Here you can do the clean up, save the parameters (if any) for the next session
//
void pluginCleanUp()
{
}

//
// Initialization of your plugin commands
// You should fill your plugins commands here
void commandMenuInit()
{

    //--------------------------------------------//
    //-- STEP 3. CUSTOMIZE YOUR PLUGIN COMMANDS --//
    //--------------------------------------------//
    // with function :
    // setCommand(int index,                      // zero based number to indicate the order of command
    //            TCHAR *commandName,             // the command name that you want to see in plugin menu
    //            PFUNCPLUGINCMD functionPointer, // the symbol of function (function pointer) associated with this command. The body should be defined below. See Step 4.
    //            ShortcutKey *shortcut,          // optional. Define a shortcut to trigger this command
    //            bool check0nInit                // optional. Make this menu item be checked visually
    //            );
    
    setCommand(0, TEXT("Compile"), piccCompile, NULL, false);
    setCommand(1, TEXT("Build Project"), buildProject, NULL, false);
    setCommand(2, TEXT("Build Options"), buildOptionsDlg, NULL, false);
    setCommand(3, TEXT("Compiler Version"), compilerVersion, NULL, false);
    setCommand(4, TEXT("---"), NULL, NULL, false);
    setCommand(5, TEXT("Supported Devices"), supportedDevices, NULL, false);
    setCommand(6, TEXT("Device Table Editor"), deviceTableEditor, NULL, false);
    setCommand(7, TEXT("Documentation Generator"), docGenerator, NULL, false);
    setCommand(8, TEXT("Signal Generator/Monitor"), signalGenerator, NULL, false);
    setCommand(9, TEXT("Numeric Converter"), numConvert, NULL, false);
    setCommand(10, TEXT("COFF Debug"), coffDump, NULL, false);
    setCommand(11, TEXT("---"), NULL, NULL, false);
    setCommand(12, TEXT("PCB, PCM, and PCH Wizard"), pcbWizard, NULL, false);
    setCommand(13, TEXT("PCD Wizard"), pcdWizard, NULL, false);
    setCommand(14, TEXT("---"), NULL, NULL, false);
    setCommand(15, TEXT("PCB, PCM, and PCH Help"), pcbHelp, NULL, false);
    setCommand(16, TEXT("PCD Help"), pcdHelp, NULL, false);
}

//
// Here you can do the clean up (especially for the shortcut)
//
void commandMenuCleanUp()
{
	// Don't forget to deallocate your shortcut here
}


//
// This function help you to initialize your plugin commands
//
bool setCommand(size_t index, TCHAR *cmdName, PFUNCPLUGINCMD pFunc, ShortcutKey *sk, bool check0nInit) 
{
    if (index >= nbFunc)
        return false;

    if (!pFunc)
        return false;

    lstrcpy(funcItem[index]._itemName, cmdName);
    funcItem[index]._pFunc = pFunc;
    funcItem[index]._init2Check = check0nInit;
    funcItem[index]._pShKey = sk;

    return true;
}

//----------------------------------------------//
//-- STEP 4. DEFINE YOUR ASSOCIATED FUNCTIONS --//
//----------------------------------------------//


// -----------------------------------------------------------------------------

int Ccsc(LPCTSTR program, LPCTSTR command, LPCTSTR filename, std::string& stdOut, std::string& stdError);
void ShowError(int exitCode, const std::string& stdOut, const std::string& stdError);
void ShowLineError(const std::string& stdOut);
void anotationClear();
HWND getCurrentScintilla();
int showMessageBox(TCHAR* text = TEXT(""), int flags = MB_OK);
HINSTANCE execute(TCHAR* program, TCHAR* params = NULL);
enum MARKER_ID
{
    MARKER_ERROR_SYMBOL = 30,
    MARKER_WARNING_SYMBOL = 25
};
// -----------------------------------------------------------------------------

void coffDump()
{
	_TCHAR filename[_MAX_FNAME];
	::SendMessage(nppData._nppHandle, NPPM_GETNAMEPART, 0, (LPARAM)filename);
	_TCHAR currentdirectory[_MAX_PATH];
	::SendMessage(nppData._nppHandle, NPPM_GETCURRENTDIRECTORY, 0, (LPARAM)currentdirectory);
	lstrcat(currentdirectory, TEXT("\\"));
	lstrcat(currentdirectory, filename);
	lstrcat(currentdirectory, TEXT(".cof"));
	std::string output, errors;
  	if(!PathFileExists(currentdirectory)){
		showMessageBox(TEXT("Dont have COFF file"));
    return;
	}
	int exitCode = Ccsc(TEXT("ccscoff.exe") , TEXT(""), currentdirectory, output, errors);
	if(exitCode != 0) 
	{
		ShowError(exitCode, output, errors);
	}
     // Open a new document
    ::SendMessage(nppData._nppHandle, NPPM_MENUCOMMAND, 0, IDM_FILE_NEW);
    // Get the current scintilla
    int which = -1;
    ::SendMessage(nppData._nppHandle, NPPM_GETCURRENTSCINTILLA, 0, (LPARAM)&which);
    if (which == -1)
        return;
    HWND curScintilla = (which == 0)?nppData._scintillaMainHandle:nppData._scintillaSecondHandle;
    // Say hello now :
    // Scintilla control has no Unicode mode, so we use (char *) here
    if (output.length()<=0) output = "";
    char* dest = new char [output.length()+1];
    strcpy_s(dest, output.length(), output.c_str());
    
    ::SendMessage(curScintilla, SCI_SETTEXT, 0, (LPARAM)dest);
}

void buildOptionsDlg()
{

}

void compilerVersion()
{
  execute(TEXT("Ccsc.exe"), TEXT("+V"));
}

void pcbHelp()
{
  execute(TEXT("Ccsc.chm"));
}

void pcdHelp()
{
  execute(TEXT("pcd.chm"));
}

void supportedDevices()
{
  execute(TEXT("Ccsc.exe"), TEXT("+Q"));
}

void deviceTableEditor()
{   
  execute(TEXT("Chipedit.exe"));
}

void numConvert()
{   
  execute(TEXT("Pconvert.exe"));
}

void buildProject()
{   
	_TCHAR filename[_MAX_FNAME];
	::SendMessage(nppData._nppHandle, NPPM_GETNAMEPART, 0, (LPARAM)filename);
	_TCHAR currentdirectory[_MAX_PATH];
	::SendMessage(nppData._nppHandle, NPPM_GETCURRENTDIRECTORY, 0, (LPARAM)currentdirectory);
  _TCHAR paramsBuild[_MAX_PATH]=TEXT("+FM BUILD=\"");
	lstrcat(paramsBuild, currentdirectory);
	lstrcat(paramsBuild, TEXT("\\"));
	lstrcat(paramsBuild, filename);
	lstrcat(paramsBuild, TEXT(".pjt\""));
  execute(TEXT("Ccsc.exe"), paramsBuild);
}

void docGenerator()
{   
  //TODO
  execute(TEXT("documentationgenerator.exe"));
}

void signalGenerator()
{   
  execute(TEXT("CCSSignal.exe"));
}

void pcbWizard()
{   
  execute(TEXT("pcwwiz.exe"));
}
void pcdWizard()
{   
  execute(TEXT("PcdWiz.exe"));
}

void piccCompile()
{
	_TCHAR filename[_MAX_PATH];
	::SendMessage(nppData._nppHandle, NPPM_GETFULLCURRENTPATH, 0, (LPARAM)filename);
	if(::GetFileAttributes(filename) == INVALID_FILE_ATTRIBUTES)
	{
		// file does not exist on disk yet.
    //showMessageBox(TEXT("File has not been saved yet, so it can't be compiled\nSave it and try again."));
		if (!::SendMessage(nppData._nppHandle, NPPM_SAVECURRENTFILE, 0, (LPARAM)"main.c")) // the cancel button of savedialog is pressed, aborts closing
			return;
		::SendMessage(nppData._nppHandle, NPPM_GETFULLCURRENTPATH, 0, (LPARAM)filename);
	}
	_TCHAR filext[_MAX_FNAME] = TEXT("");
	::SendMessage(nppData._nppHandle, NPPM_GETEXTPART, 0, (LPARAM)filext);
	std::string output, errors, result;
	int exitCode;
	if(lstrcmpi(filext, TEXT(".c"))){
		exitCode = Ccsc(TEXT("Ccsc.exe") , TEXT("+STDOUT -L -J -D +EA"), TEXT(""), output, errors);
		return;
	}
		::SendMessage(nppData._nppHandle, NPPM_SAVECURRENTFILE, 0, 0);
		exitCode = Ccsc(TEXT("Ccsc.exe") , TEXT("+STDOUT -L -J -D +EA"), filename, output, errors);
	//int exitCode = Ccsc(TEXT("+STDOUT +FM +ES +J +DC +Y9 -T -A +M +LNlst +O8hex -P -Z"), filename, output, errors);
	//int exitCode = Ccsc(TEXT("+STDOUT +FM -L -T -A -J -D -P -M +EA"), filename, output, errors);  
	if(exitCode != 0) 
	{
		ShowError(exitCode, output, errors);
	}
    std::vector<TCHAR> buffer(512 + errors.size());
    _stprintf_s(&buffer[0], buffer.size(), TEXT("%hs"), errors.c_str());
	
//    showMessageBox(&buffer[0]);
 wchar_t * str=   TEXT(" Memory");
wchar_t * string = &buffer[0];
   wchar_t *pdest;
   pdest = wcsstr( string, str );
//   int  result2;
  //result2 = (int)(pdest +0);
    //_stprintf_s(&buffer[1], buffer.size(), TEXT("%hs"), result2);
	::SendMessage(nppData._nppHandle, NPPM_SETSTATUSBAR, STATUSBAR_DOC_TYPE, (LPARAM)pdest);
     anotationClear(); 
        HWND curScintilla = getCurrentScintilla();   
        ::SendMessage(curScintilla, SCI_ANNOTATIONSETTEXT, 10, (LPARAM)" Error[70] No main() function found");
        
        ::SendMessage(curScintilla, SCI_ANNOTATIONSETSTYLE, 10, 39);
        ::SendMessage(curScintilla, SCI_ANNOTATIONSETVISIBLE, 10, 0);        
        
        ::SendMessage(curScintilla, SCI_ANNOTATIONSETTEXT, 5, (LPARAM)" Warning");
        
        ::SendMessage(curScintilla, SCI_ANNOTATIONSETSTYLE, 5, 40);
        ::SendMessage(curScintilla, SCI_ANNOTATIONSETVISIBLE, 5, 0);     
			
				
//		::SendMessageA(curScintilla, SCI_MARKERDEFINE, 30, (LPARAM)SC_MARK_CHARACTER+65);			
// #include "icon_warning_16.h"
// #include "icon_sub_16.h"
// #include "icon_moved_16.h"
// #include "icon_sub_16.h"
//		::SendMessageA(curScintilla, SCI_MARKERDEFINEPIXMAP, (LPARAM)MARKER_ERROR_SYMBOL, (LPARAM)&icon_error_16_xpm[0]);			
//		::SendMessageA(curScintilla, SCI_MARKERDEFINEPIXMAP, (LPARAM)MARKER_WARNING_SYMBOL, (LPARAM)&icon_warning_16_xpm[0]);			
//		::SendMessageA(curScintilla, SCI_MARKERADD, 5, (LPARAM)MARKER_WARNING_SYMBOL);	
//		::SendMessageA(curScintilla, SCI_MARKERADD, 10, (LPARAM)MARKER_ERROR_SYMBOL);	
		
/* 

SCI_MARKERDEFINE(int markerNumber, int markerSymbols)
SCI_MARKERDEFINEPIXMAP(int markerNumber, const char *xpm)
SCI_MARKERSYMBOLDEFINED(int markerNumber)
SCI_MARKERSETFORE(int markerNumber, int colour)
SCI_MARKERSETBACK(int markerNumber, int colour)
SCI_MARKERSETBACKSELECTED(int markerNumber, int colour)
SCI_MARKERENABLEHIGHLIGHT(int enabled)
SCI_MARKERSETALPHA(int markerNumber, int alpha)
SCI_MARKERADD(int line, int markerNumber)
SCI_MARKERADDSET(int line, int markerMask)
SCI_MARKERDELETE(int line, int markerNumber)
SCI_MARKERDELETEALL(int markerNumber)
SCI_MARKERGET(int line)
SCI_MARKERNEXT(int lineStart, int markerMask)
SCI_MARKERPREVIOUS(int lineStart, int markerMask)
SCI_MARKERLINEFROMHANDLE(int handle)
SCI_MARKERDELETEHANDLE(int handle)
*/
		
		//::SendMessageA(curScintilla, SCI_MARKERADDSET, 1, marker);			
   
   //char* dest = new char [output.length()+1];
}

// -----------------------------------------------------------------------------

void ShowError(int exitCode, const std::string& stdOut, const std::string& stdError)
{
	std::vector<TCHAR> buffer(512 + stdOut.size() + stdError.size());
	_stprintf_s(&buffer[0], buffer.size(), TEXT("Error code %d\n%hs\n%hs"), exitCode, stdError.c_str(), stdOut.c_str());
  showMessageBox(&buffer[0], MB_OK|MB_ICONERROR);
}

void ShowLineError(const std::string& stdError)
{
	std::vector<TCHAR> buffer(512 + stdError.size());
	_stprintf_s(&buffer[0], buffer.size(), TEXT("%hs"), stdError.c_str());
  showMessageBox(&buffer[0], MB_OK|MB_ICONERROR);
  
/*    
      Memory usage:   ROM=16%      RAM=3% - 4%
      0 Errors,  0 Warnings.
    */
}
int Ccsc(LPCTSTR program, LPCTSTR command, LPCTSTR filename, std::string& stdOut, std::string& stdError)
{
	ITEMIDLIST *pidl;
	TCHAR programFiles[_MAX_PATH];
	SHGetSpecialFolderLocation(NULL, CSIDL_PROGRAM_FILESX86, &pidl);
	SHGetPathFromIDList(pidl, programFiles);
	lstrcat(programFiles, TEXT("\\PICC\\"));
	lstrcat(programFiles, program);
	if(!PathFileExists(programFiles)){
		showMessageBox(TEXT("Dont have installed"));
    return 1;
	}
	
  PathQuoteSpaces(programFiles);
	const size_t COMMAND_BUFFER_SIZE = 512;
	TCHAR commandBuffer[COMMAND_BUFFER_SIZE];
	_tcscpy_s(commandBuffer, programFiles);
	_tcscat_s(commandBuffer, TEXT(" "));
	_tcscat_s(commandBuffer, command);
	_tcscat_s(commandBuffer, TEXT(" \""));
	_tcscat_s(commandBuffer, filename);
	_tcscat_s(commandBuffer, TEXT("\""));

  //showMessageBox(commandBuffer);
  
	DWORD exitCode = 0;
	STARTUPINFO startupInfo;
	ZeroMemory(&startupInfo, sizeof(startupInfo));
	startupInfo.cb = sizeof(startupInfo);
	startupInfo.dwFlags = STARTF_USESTDHANDLES;

	PROCESS_INFORMATION procInfo;
	ZeroMemory(&procInfo, sizeof(procInfo));

	TempFile stdOutFile;
	TempFile stdErrorFile;
	startupInfo.hStdError = stdErrorFile.GetHandle();
	startupInfo.hStdOutput = stdOutFile.GetHandle();
  
	if(CreateProcess(0, commandBuffer, NULL, NULL, TRUE, CREATE_NO_WINDOW, 0, 0, &startupInfo, &procInfo))
	{
    WaitForSingleObject(procInfo.hProcess, INFINITE);

		GetExitCodeProcess(procInfo.hProcess, &exitCode);
		CloseHandle(procInfo.hThread);
		CloseHandle(procInfo.hProcess);
    
		stdOut = stdOutFile.GetFileContents();
		stdError = stdErrorFile.GetFileContents();
	}
	else
	{
		const size_t ERR_BUFFER_SIZE = 512;
		exitCode = GetLastError(); 
		TCHAR buffer[ERR_BUFFER_SIZE]; 
		LPVOID lpMsgBuf;
		FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER|FORMAT_MESSAGE_FROM_SYSTEM,0, exitCode, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpMsgBuf,0,0);
		_stprintf_s(buffer, ERR_BUFFER_SIZE, TEXT("Ccsc%s failed with error %d: %s"), command, exitCode, lpMsgBuf); 
		LocalFree(lpMsgBuf);
#ifdef UNICODE
		char charBuffer[ERR_BUFFER_SIZE];
		::WideCharToMultiByte(CP_ACP, 0, buffer,-1, charBuffer, ERR_BUFFER_SIZE, 0,0);
		stdError.assign(charBuffer);
#else
		stdError.assign(buffer);
#endif
	}
	return exitCode;

}

HWND getCurrentScintilla()
{
    int which = -1;
    ::SendMessage(nppData._nppHandle, NPPM_GETCURRENTSCINTILLA, 0, (LPARAM)&which);
    if (which == -1)
        return NULL;
    if (which == 0)
    {
        return nppData._scintillaMainHandle;
    }
    else
    {
        return nppData._scintillaSecondHandle;
    }
    return nppData._scintillaMainHandle;
}

int showMessageBox(TCHAR* text, int flags)
{
    return ::MessageBox(nppData._nppHandle, text, getName(), flags);
}

HINSTANCE execute(TCHAR* program, TCHAR* params)
{
TCHAR *opVerb = TEXT("open"); 
	//enum winVer{WV_UNKNOWN, WV_WIN32S, WV_95, WV_98, WV_ME, WV_NT, WV_W2K, WV_XP, WV_S2003, WV_XPX64, WV_VISTA, WV_WIN7};
	winVer winVersion = WV_UNKNOWN;
	::SendMessage(nppData._nppHandle, NPPM_GETWINDOWSVERSION, 0, (LPARAM)winVersion);
	if (winVersion == WV_VISTA || winVersion == WV_WIN7)
		opVerb = TEXT("runas");
  	ITEMIDLIST *pidl;
	_TCHAR programFiles[_MAX_PATH];
	SHGetSpecialFolderLocation(NULL, CSIDL_PROGRAM_FILESX86, &pidl);
	SHGetPathFromIDList(pidl, programFiles);
	lstrcat(programFiles, TEXT("\\PICC\\"));
	lstrcat(programFiles, program);
	if(PathFileExists(programFiles)){
		PathQuoteSpaces(programFiles);
    return ShellExecute(NULL, opVerb, programFiles, params, NULL, SW_SHOWNORMAL);
	}else {
  
    showMessageBox(TEXT("Dont have installed"));
    return NULL;
  }
}

void anotationClear()
{
  ::SendMessage(getCurrentScintilla(), SCI_ANNOTATIONCLEARALL, 0, 0);
}
