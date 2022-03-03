#include <iostream>
#include "flatbuffers/SchemaTest_generated.h"
#include <unicode/ustring.h>
#include <unicode/unistr.h>
#include <utility>
#include <Windows.h>

int main()
{
	SetConsoleOutputCP(CP_UTF8);
	setlocale(LC_ALL, "en_US.UTF-8");

	flatbuffers::FlatBufferBuilder builder;
	MyGame::Vec3 vec3{ 123.456f, 789.123f, 456.789f };
	std::vector<unsigned char> vector{ 12, 34, 56, 78, 90 };

	std::string name = "اللغة العربية 한국어 日本語 妈妈, 我们不能养一只波斯猫吗 คุณด้วยนะคะ Монгол хэл русский français";
	auto monster = MyGame::CreateMonster(builder, &vec3, 12345, 9876, builder.CreateString(name), builder.CreateVector(vector), MyGame::Color_Green);

	builder.Finish(monster);

	auto monsterPtr = builder.GetBufferPointer();
	auto monsterPtrSize = builder.GetSize();

	auto monster2 = MyGame::GetMonster(monsterPtr);
	
	std::cout << "pos : { " << monster2->pos()->x() << ", " << monster2->pos()->y() << ", " << monster2->pos()->z() << " }" << std::endl;
	std::cout << "mana : " << monster2->mana() << std::endl;
	std::cout << "hp : " << monster2->hp() << std::endl;
	std::cout << "name : " << monster2->name()->c_str() << std::endl;
	std::cout << "inventory : ";
	for (auto it = monster2->inventory()->begin(); it != monster2->inventory()->end(); it++)
	{
		std::cout << (int)(*it) << ", ";
	}
	std::cout << std::endl;

	std::cout << "color : " << (int)monster2->color() << std::endl;



	std::u8string u8string = u8"اللغة العربية 한국어 日本語 妈妈, 我们不能养一只波斯猫吗 คุณด้วยนะคะ Монгол хэл русский français";
	std::string string = reinterpret_cast<const char*>(u8"اللغة العربية 한국어 日本語 妈妈, 我们不能养一只波斯猫吗 คุณด้วยนะคะ Монгол хэл русский français");

	std::cout << sizeof(char8_t) << std::endl;;
	std::cout << sizeof(char) << std::endl;;


	auto u8stringBuffer = u8string.c_str();
	auto stringBuffer = string.c_str();
	std::cout << reinterpret_cast<const char*>(u8string.c_str()) << std::endl;
	for (int i = 0; i < u8string.length(); i++)
	{
		std::cout << static_cast<int>(u8stringBuffer[i]) << std::endl;
	}

	std::cout << std::endl;
	std::cout << "-------------------------------------------------------------------------------" << std::endl;
	std::cout << std::endl;

	for (int i = 0; i < string.length(); i++)
	{
		std::cout << static_cast<int>(static_cast<unsigned char>(stringBuffer[i])) << std::endl;
	}
}