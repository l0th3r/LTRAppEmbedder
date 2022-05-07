#pragma once

#include <string>
#include <fstream>

namespace ltr
{
	enum class OpenMode : int
	{
		Read,
		Write,
		Rewrite,
		Modify,
	};

	struct File
	{
	public:
		std::string content;
		bool isValid;

		File(const char* path, OpenMode mode = OpenMode::Read);
		~File();

	private:
		void UpdateContent();

	protected:
		std::fstream stream;
		OpenMode mode;

		static const char* GetOpenModeCode(OpenMode mode);
	};
}