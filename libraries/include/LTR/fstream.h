#pragma once

#include <stdio.h>

namespace ltr
{
	struct File
	{
	public:
		File(const char* path);
		~File();

	protected:
		FILE* fptr;
	};
}