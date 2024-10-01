#include "ColorPCH.h"
#include "FileSystem.h"

#include "Platform/Windows/WindowsFileSystem.h"

namespace Color
{
	Scope<FileSystem> FileSystem::s_NativeInstance = CreateScope<CL_ConcatWithPlatformName(FileSystem)>();

	std::string FileSystem::WithoutFilename(std::string_view filepath)
	{
		const size_t lastSeperatorPos = filepath.find_last_of("/\\");
		if (lastSeperatorPos != std::string_view::npos)
		{
			return std::string(filepath.substr(0, lastSeperatorPos).data(), lastSeperatorPos + 1);
		}
		return "";
	}

	void FileSystem::RemoveFilename(std::string& filepath)
	{
		filepath = WithoutFilename(filepath);
	}

	std::string FileSystem::GetFileExtension(std::string_view filepath)
	{
		const size_t lastDotPos = filepath.rfind('.');
		return lastDotPos != std::string::npos ? std::string(filepath.substr(lastDotPos).data(), filepath.size() - lastDotPos) : "";
	}

	std::string FileSystem::CombinePaths(std::string_view lhs, std::string_view rhs, char preferredSeperator)
	{
		if (lhs.empty())
		{
			return std::string(rhs);
		}
		if (rhs.empty())
		{
			return std::string(lhs);
		}

		char seperator = preferredSeperator;
		if (seperator == '\0')
		{
			const size_t lhsLastSeperator = lhs.find_first_of("/\\");
			if (lhsLastSeperator != std::string::npos)
			{
				seperator = lhs[lhsLastSeperator];
			}
			else
			{
				const size_t rhsLastSeperator = rhs.find_first_of("/\\");
				seperator = rhsLastSeperator != std::string::npos ? rhs[rhsLastSeperator] : '/'; // fallback to '/' if no seps found.
			}
		}

		char lcLeft = lhs[lhs.size() - 1];
		char fcRight = rhs[0];

		std::string result;
		result.reserve(lhs.size() + 1 + rhs.size());

		result += lhs;
		if (lcLeft != '/' && lcLeft != '\\' && fcRight != '/' && fcRight != '\\')
		{
			result += seperator;
		}
		result += rhs;

		for (char& c : result)
		{
			if ((c == '/' || c == '\\') && c != seperator)
			{
				c = seperator;
			}
		}

		return result;
	}
}
