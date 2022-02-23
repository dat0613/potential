#include <iostream>
#include "flatbuffers/SchemaTest_generated.h"

int main()
{
	flatbuffers::FlatBufferBuilder builder;
	MyGame::Vec3 vec3{ 123.456f, 789.123f, 456.789f };
	std::vector<unsigned char> vector{ 12, 34, 56, 78, 90 };
	auto monster = MyGame::CreateMonster(builder, &vec3, 12345, 9876, builder.CreateString("Monster"), builder.CreateVector(vector), MyGame::Color_Green);

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
}