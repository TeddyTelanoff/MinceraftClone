#pragma once

#include <cstdio>
#include <string>

std::string ReadFile(const std::string& filepath)
{
	FILE* fs = fopen(filepath.c_str(), "rb");
	
	fseek(fs, 0, SEEK_END);
	const int size = ftell(fs);
	const int allocaSize = size + 1;
	char* buff = (char*)_malloca(allocaSize);
	rewind(fs);

	if (buff == nullptr)
	{
		fclose(fs);
		return "";
	}

	fread(buff, sizeof(char), size, fs);
	fclose(fs);
	buff[size] = 0;

	return buff;
}

void WriteFile(const std::string& filepath, const std::string& text)
{
	FILE* fs = fopen(filepath.c_str(), "w+");

	fputs(text.c_str(), fs);
	fflush(fs);
	
	fclose(fs);
}