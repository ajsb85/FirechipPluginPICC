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
 
#pragma once
#ifndef NPPPERFORCEPLUGIN_TEMPFILE_H
#define NPPPERFORCEPLUGIN_TEMPFILE_H

class TempFile
{
public:
	TempFile() : handle(INVALID_HANDLE_VALUE)
	{
		TCHAR cname[MAX_PATH];
		TCHAR tmpdir[MAX_PATH];
		GetTempPath(MAX_PATH, tmpdir);
		GetTempFileName(tmpdir,TEXT("ccsc"), 0, cname);
		name = cname;

		SECURITY_ATTRIBUTES sa;
		sa.nLength= sizeof(SECURITY_ATTRIBUTES);
		sa.lpSecurityDescriptor = NULL;
		sa.bInheritHandle = TRUE;

		handle = CreateFile(cname, GENERIC_READ|GENERIC_WRITE, FILE_SHARE_READ, &sa, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
	}

	~TempFile()
	{
		if(handle != INVALID_HANDLE_VALUE)
		{
			FlushFileBuffers(handle);
			CloseHandle(handle);
		}
		DeleteFile(name.c_str());
	}

	HANDLE GetHandle() const { return handle; }

	std::string GetFileContents()
	{
		std::string retval;
		DWORD size = SetFilePointer(handle, 0, 0, FILE_CURRENT);
		if(size > 0)
		{
			std::vector<char> buffer(size);
			SetFilePointer(handle, 0,0,FILE_BEGIN);
			DWORD numRead;
			ReadFile(handle, &buffer[0], size, &numRead, 0);
			retval.assign(&buffer[0], &buffer[0] + numRead);
		}
		return retval;
	}

private:
	HANDLE handle;
#ifdef UNICODE
	std::wstring name;
#else
	std::string name;
#endif
};



#endif

