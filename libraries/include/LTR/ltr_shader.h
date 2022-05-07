#pragma once

#include <string>

namespace ltr
{
	struct Shader
	{
	public:
		Shader(const std::string filepath, const unsigned int type);

	public:
		std::string file;
		std::string rawContent;
		unsigned int type;
	};
}