#pragma once

#include "Utils/FileSystem.h"

namespace Color
{
	class WindowsFileSystem : public FileSystem
	{
	protected:
		virtual bool Exists_(std::string_view path) override;
		virtual bool IsFile_(std::string_view path) override;
		virtual bool IsDirectory_(std::string_view path) override;

		virtual std::string GetWorkingDirectory_() override;
		virtual bool SetWorkingDirectory_(std::string_view path) override;

		virtual std::string Rel_(std::string_view path) override;
		virtual std::string Abs_(std::string_view path) override;

		virtual bool Read_(std::string_view filepath, std::string& o_Data) override;
		virtual bool Write_(std::string_view filepath, std::string_view data, bool append) override;
	};
}
