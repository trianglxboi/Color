#pragma once

#include "Core/Base.h"

#include <string_view>
#include <string>

namespace Color
{
	class FileSystem
	{
	public:
		virtual ~FileSystem() = default;

		static bool Exists(std::string_view path) { return s_NativeInstance->Exists_(path); }
		static bool IsFile(std::string_view path) { return s_NativeInstance->IsFile_(path); }
		static bool IsDirectory(std::string_view path) { return s_NativeInstance->IsDirectory_(path); }

		static std::string GetWorkingDirectory() { return s_NativeInstance->GetWorkingDirectory_(); }
		static bool SetWorkingDirectory(std::string_view path) { return s_NativeInstance->SetWorkingDirectory_(path); }

		static std::string Rel(std::string_view path) { return s_NativeInstance->Rel_(path); }
		static std::string Abs(std::string_view path) { return s_NativeInstance->Abs_(path); }

		static bool Read(std::string_view filepath, std::string& o_Data) { return s_NativeInstance->Read_(filepath, o_Data); }
		static bool Write(std::string_view filepath, std::string_view data, bool append = false) { return s_NativeInstance->Write_(filepath, data, append); }
	protected:
		virtual bool Exists_(std::string_view path) = 0;
		virtual bool IsFile_(std::string_view path) = 0;
		virtual bool IsDirectory_(std::string_view path) = 0;

		virtual std::string GetWorkingDirectory_() = 0;
		virtual bool SetWorkingDirectory_(std::string_view path) = 0;

		virtual std::string Rel_(std::string_view path) = 0;
		virtual std::string Abs_(std::string_view path) = 0;

		virtual bool Read_(std::string_view filepath, std::string& o_Data) = 0;
		virtual bool Write_(std::string_view filepath, std::string_view data, bool append) = 0;
	private:
		static Scope<FileSystem> s_NativeInstance;
	};
}
