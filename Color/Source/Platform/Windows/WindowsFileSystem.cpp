#include "ColorPCH.h"
#include "WindowsFileSystem.h"

#include <Shlwapi.h>

namespace Color
{
	static DWORD g_dwReadFileBytesTransfered = 0;

	VOID CALLBACK ReadFileIOCompletionRoutine
	(
		__in DWORD        dwErrorCode,
		__in DWORD        dwNumberOfBytesTransfered,
		__in LPOVERLAPPED lpOverlapped
	)
	{
		g_dwReadFileBytesTransfered = dwNumberOfBytesTransfered;
	}

	bool WindowsFileSystem::Exists_(std::string_view path)
	{
		DWORD dwAttrib = GetFileAttributesA(path.data());
		return dwAttrib != INVALID_FILE_ATTRIBUTES;
	}

	bool WindowsFileSystem::IsFile_(std::string_view path)
	{
		DWORD dwAttrib = GetFileAttributesA(path.data());
		return (dwAttrib != INVALID_FILE_ATTRIBUTES) && !(dwAttrib & FILE_ATTRIBUTE_DIRECTORY);
	}

	bool WindowsFileSystem::IsDirectory_(std::string_view path)
	{
		DWORD dwAttrib = GetFileAttributesA(path.data());
		return (dwAttrib != INVALID_FILE_ATTRIBUTES) && (dwAttrib & FILE_ATTRIBUTE_DIRECTORY);
	}

	std::string WindowsFileSystem::GetWorkingDirectory_()
	{
		std::string wdir(MAX_PATH, '\0');

		if (GetCurrentDirectoryA(MAX_PATH, wdir.data()) == 0)
		{
			return "";
		}

		return wdir;
	}

	bool WindowsFileSystem::SetWorkingDirectory_(std::string_view path)
	{
		return SetCurrentDirectoryA(path.data());
	}

	std::string WindowsFileSystem::Rel_(std::string_view path)
	{
		std::string rel(MAX_PATH, '\0');
		std::string wdir = GetWorkingDirectory();

		DWORD dwResult = PathRelativePathToA(rel.data(), wdir.data(), FILE_ATTRIBUTE_DIRECTORY, path.data(), IsDirectory(path) ? FILE_ATTRIBUTE_DIRECTORY : FILE_ATTRIBUTE_NORMAL);
		if (dwResult == 0)
		{
			return "";
		}

		return rel;
	}

	std::string WindowsFileSystem::Abs_(std::string_view path)
	{
		std::string abs(MAX_PATH, '\0');

		if (GetFullPathNameA(path.data(), MAX_PATH, abs.data(), NULL) == 0)
		{
			return "";
		}

		return abs;
	}

	bool WindowsFileSystem::Read_(std::string_view filepath, std::string& o_Data)
	{
		HANDLE hFile = CreateFileA
		(
			filepath.data(),
			GENERIC_READ,
			FILE_SHARE_READ,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED,
			NULL
		);

		if (hFile == INVALID_HANDLE_VALUE)
		{
			return false;
		}

		LARGE_INTEGER liFileSize;
		if (!GetFileSizeEx(hFile, &liFileSize))
		{
			CloseHandle(hFile);
			return false;
		}
		o_Data = std::string(liFileSize.QuadPart, '\0');

		OVERLAPPED ol = { 0 };
		BOOL bReadState = ReadFileEx(hFile, o_Data.data(), (DWORD) liFileSize.QuadPart, &ol, ReadFileIOCompletionRoutine);

		if (bReadState == FALSE)
		{
			CloseHandle(hFile);
			return false;
		}

		SleepEx(500000, TRUE);

		if (g_dwReadFileBytesTransfered != liFileSize.QuadPart)
		{
			CloseHandle(hFile);
			return false;
		}

		CloseHandle(hFile);
		return true;
	}

	bool WindowsFileSystem::Write_(std::string_view filepath, std::string_view data, bool append)
	{
		HANDLE hFile = CreateFileA
		(
			filepath.data(),
			append ? FILE_APPEND_DATA : GENERIC_WRITE,
			NULL,
			NULL,
			Exists(filepath) ? (append ? OPEN_EXISTING : TRUNCATE_EXISTING) : CREATE_NEW,
			FILE_ATTRIBUTE_NORMAL,
			NULL
		);

		if (hFile == INVALID_HANDLE_VALUE)
		{
			return false;
		}

		DWORD dwBytesWritten;
		BOOL  bWriteState = WriteFile(hFile, data.data(), (DWORD) data.size(), &dwBytesWritten, NULL);

		if (bWriteState == FALSE || dwBytesWritten != data.size())
		{
			CloseHandle(hFile);
			return false;
		}

		CloseHandle(hFile);
		return true;
	}
}
