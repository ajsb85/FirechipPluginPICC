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

#ifndef M30_IDE_COMMUN_H
#define M30_IDE_COMMUN_H

#include <windows.h>
#include <string>
#include <vector>
#include <time.h>

void systemMessage(const TCHAR *title);
//DWORD ShortToLongPathName(LPCTSTR lpszShortPath, LPTSTR lpszLongPath, DWORD cchBuffer);
void printInt(int int2print);
void printStr(const TCHAR *str2print);
void writeLog(const TCHAR *logFileName, const TCHAR *log2write);
int filter(unsigned int code, struct _EXCEPTION_POINTERS *ep);
int getCpFromStringValue(const TCHAR * encodingStr);
std::basic_string<TCHAR> purgeMenuItemString(const TCHAR * menuItemStr, bool keepAmpersand = false);

#define CP_ANSI_LATIN_1 1252
#define CP_BIG5 950

#ifdef UNICODE
	#define NppMainEntry wWinMain
	#define generic_strtol wcstol
	#define generic_strncpy wcsncpy
	#define generic_stricmp _wcsicmp
	#define generic_strncmp wcsncmp
	#define generic_strnicmp wcsnicmp
	#define generic_strncat wcsncat
	#define generic_strchr wcschr
	#define generic_atoi _wtoi
	#define generic_atof _wtof
	#define generic_strtok wcstok
	#define generic_strftime wcsftime
	#define generic_fprintf fwprintf
	#define generic_sscanf swscanf
	#define generic_fopen _wfopen_s
	#define generic_fgets fgetws
	#define generic_stat _wstat
	#define COPYDATA_FILENAMES COPYDATA_FILENAMESW
#else
	#define NppMainEntry WinMain
	#define generic_strtol strtol
	#define generic_strncpy strncpy
	#define generic_stricmp stricmp
	#define generic_strncmp strncmp
	#define generic_strnicmp strnicmp
	#define generic_strncat strncat
	#define generic_strchr strchr
	#define generic_atoi atoi
	#define generic_atof atof
	#define generic_strtok strtok
	#define generic_strftime strftime
	#define generic_fprintf fprintf
	#define generic_sscanf sscanf
	#define generic_fopen fopen
	#define generic_fgets fgets
	#define generic_stat _stat
	#define COPYDATA_FILENAMES COPYDATA_FILENAMESA
#endif

//void char2wchar(const char* pszCHAR, wchar_t* pszWCHAR, UINT codepage);
//void wchar2char(const wchar_t* pszWCHAR, char* pszCHAR, UINT codepage);
std::wstring string2wstring(const std::string & rString, UINT codepage);
std::string wstring2string(const std::wstring & rwString, UINT codepage);


class WcharMbcsConvertor {
public:
	static WcharMbcsConvertor * getInstance() {return _pSelf;};
	static void destroyInstance() {delete _pSelf;};

	const wchar_t * char2wchar(const char* mbStr, UINT codepage);
	const char * wchar2char(const wchar_t* wcStr, UINT codepage);

protected:
	WcharMbcsConvertor() : _multiByteStr(NULL), _wideCharStr(NULL), _multiByteAllocLen(0), _wideCharAllocLen(0), initSize(1024) {};
	~WcharMbcsConvertor() {
		if (_multiByteStr)
			delete [] _multiByteStr;
		if (_wideCharStr)
			delete [] _wideCharStr;
	};
	static WcharMbcsConvertor * _pSelf;

	const int initSize;
	char *_multiByteStr;
	size_t _multiByteAllocLen;
	wchar_t *_wideCharStr;
	size_t _wideCharAllocLen;
	
};


#endif //M30_IDE_COMMUN_H
