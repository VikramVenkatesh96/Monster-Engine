#include "Loader.h"
//Component classes
#pragma region Components
#include "RigidBody2D.h"
#include "SpriteRenderer.h"
#include "Input.h"
#include "Controller.h"
#pragma endregion
#include "RapidJSON/document.h"
#include "RapidJSON/filereadstream.h"
#include "Sprite.h"
#include "World.h"
#include <assert.h>
#include <locale>
#include <codecvt>
#include <cstdio>

using namespace rapidjson;
std::string Loader::objectFile;

Loader::Loader()
{
}


void Loader::CreateObjectsFromFile(std::string i_fileName)
{
	objectFile = i_fileName;
	//Read JSON file and store in buffer
	FILE* fp = fopen(i_fileName.c_str(), "rb");
	char readBuffer[65536];
	FileReadStream rs(fp,readBuffer, sizeof(readBuffer));
	
	Document doc;
	doc.ParseStream(rs);

	assert(doc.HasMember("gameobjects") && doc["gameobjects"].IsArray());
	const Value& objects = doc["gameobjects"];
	assert(objects.IsArray());
	for (SizeType i = 0; i < objects.Size(); ++i)
	{
		std::string name = objects[i]["name"].GetString();
		const Value& params = objects[i]["params"];
		const HashedString type(objects[i]["type"].GetString());
		if (type == "Sprite")
		{
			float posX = params["position"][0].GetFloat();
			float posY = params["position"][1].GetFloat();
			//Create GameObject with these params
			World::AddGameObject(SmartPtr<Sprite>(new Sprite(posX, posY)));
		}
	}
	fclose(fp);
}

void Loader::InitializeObjectsFromFile()
{
	assert(!objectFile.empty());
	//Read JSON file and store in buffer
	FILE* fp = fopen(objectFile.c_str(), "rb");
	char readBuffer[65536];
	FileReadStream rs(fp, readBuffer, sizeof(readBuffer));

	Document doc;
	doc.ParseStream(rs);
	const Value& objects = doc["gameobjects"];

	std::vector<SmartPtr<GameObject>> gameObjects = World::GetGameObjects();
	for (SizeType i = 0; i < gameObjects.size(); ++i)
	{
		if (objects[i]["params"].HasMember("components"))
		{
			const Value& components = objects[i]["params"]["components"];
			assert(components.IsArray());
			for (SizeType j = 0; j < components.Size(); ++j)
			{
				const Value& params = components[j]["params"];
				const HashedString type(components[j]["type"].GetString());
				if (type == "Controller")
				{
					ControllerType conType;
					const HashedString paramType(params["type"].GetString());
					if (paramType == "Player")
					{
						conType = ControllerType::Player;
					}
					else
					{
						conType = ControllerType::AI;
					}
					float maxForce = params["maxForce"].GetFloat();

					gameObjects[i]->AddComponent(SmartPtr<Component>(new Controller(*gameObjects[i], conType, maxForce)));
				}
				if (type == "Input")
				{
					gameObjects[i]->AddComponent(SmartPtr<Component>(new Input(*gameObjects[i])));
				}
				if (type == "RigidBody2D")
				{
					float mass = params["mass"].GetFloat();
					bool enableGravity = params["gravityEnabled"].GetBool();
					bool enableDrag = params["dragEnabled"].GetBool();
					gameObjects[i]->AddComponent(SmartPtr<Component>(new RigidBody2D(*gameObjects[i], mass, enableGravity, enableDrag)));
				}
				if (type == "SpriteRenderer")
				{
					std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
					std::wstring fileName = converter.from_bytes(params["fileName"].GetString());
					gameObjects[i]->AddComponent(SmartPtr<Component>(new SpriteRenderer(*gameObjects[i], fileName)));
				}
			}
		}
	}

	fclose(fp);
}
