#pragma once
#include <string>

class Loader
{
public:
	Loader();
	static void CreateObjectsFromFile(std::string);
	static void InitializeObjectsFromFile();
private:
	static std::string objectFile;
};

