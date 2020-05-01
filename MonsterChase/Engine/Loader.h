#pragma once
#include <string>
class Loader
{
public:
	Loader();
	~Loader();
	static void CreateObjectsFromFile(std::string);
};

