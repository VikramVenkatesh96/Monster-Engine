#include "Loader.h"
#include "RapidJSON/filereadstream.h"
#include "RapidJSON/document.h"
#include <cstdio>

using namespace rapidjson;
Loader::Loader()
{
}


Loader::~Loader()
{
}

void Loader::CreateObjectsFromFile(std::string i_fileName)
{
	//Read JSON file and store in buffer
	FILE* fp = fopen(i_fileName.c_str(), "rb");
	char readBuffer[65536];
	FileReadStream rs(fp,readBuffer, sizeof(readBuffer));
	
	Document doc;
	doc.ParseStream(rs);

	//
	
}
