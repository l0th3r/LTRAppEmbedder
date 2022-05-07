#include "fstream.h"

using namespace ltr;

FILE* GetFile(const char* path)
{
	return fopen(path, "r");
}

File::File(const char* path)
{
	fptr = fopen(path, "r");
}