#include "ltr_file.h"

using namespace ltr;

File::File(const char* path, OpenMode _mode)
{
	mode = _mode;
	stream.open(path, (std::ios::in | std::ios::out));
	
	isValid = stream.is_open();
	UpdateContent();
}

File::~File()
{
	stream.close();
}

void File::UpdateContent()
{
	if (!isValid)
		return;

	std::string tempLine;
	while (std::getline(stream, tempLine))
	{
		content += tempLine + '\n';
	}
}

const char* File::GetOpenModeCode(OpenMode mode)
{
	switch (mode)
	{
	default:
	case OpenMode::Read:
		return "r";
		break;
	case OpenMode::Write:
		return "a";
		break;
	case OpenMode::Rewrite:
		return "w";
		break;
	case OpenMode::Modify:
		return "a+";
		break;
	}
}