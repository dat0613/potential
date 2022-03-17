#include <iostream>
#include "flatbuffers/SchemaTest_generated.h"
#include "flatbuffers/ProtocolBase_generated.h"
#include <utility>
#include <Windows.h>

void MonseterTest()
{
	flatbuffers::FlatBufferBuilder builder;
	MyGame::Vec3 vec3{ 123.456f, 789.123f, 456.789f };
	std::vector<unsigned char> vector{ 12, 34, 56, 78, 90 };

	std::string name = "اللغة العربية 한국어 日本語 妈妈, 我们不能养一只波斯猫吗 คุณด้วยนะคะ Монгол хэл русский français";
	auto monster = MyGame::CreateMonster(builder, &vec3, 12345, 9876, builder.CreateString(name), builder.CreateVector(vector), MyGame::Color_Green);

	builder.Finish(monster);

	auto monsterPtr = builder.GetBufferPointer();
	auto monsterPtrSize = builder.GetSize();

	auto monster2 = flatbuffers::GetRoot<MyGame::Monster>(monsterPtr);

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

void ProtocolTest()
{
	flatbuffers::FlatBufferBuilder builder;
	auto requestString = builder.CreateString("ThisIsRequestString!!!!");
	auto body = Protocol::CreateRequestAttack(builder, requestString);
	auto protocol = Protocol::CreateMessage(builder, Protocol::MessageType::MessageType_RequestAttack, body.Union());
	builder.Finish(protocol);

	auto ptr = builder.GetBufferPointer();

	auto protocol2 = flatbuffers::GetRoot<Protocol::Message>(ptr);

	switch (protocol2->body_type())
	{
	case Protocol::MessageType::MessageType_RequestSomeThing:
		std::cout << "MessageType_RequestSomeThing : " << protocol2->body_as_RequestSomeThing()->request_string()->c_str() << std::endl;;
		break;

	case Protocol::MessageType::MessageType_ResponseSomThing:
		std::cout << "MessageType_ResponseSomThing : " << protocol2->body_as_ResponseSomThing()->response_string()->c_str() << std::endl;;
		break;

	case Protocol::MessageType::MessageType_RequestAttack:
		std::cout << "MessageType_RequestAttack : " << protocol2->body_as_RequestAttack()->request_string()->c_str() << std::endl;;
		break;

	case Protocol::MessageType::MessageType_ResponseAttack:
		std::cout << "MessageType_ResponseAttack : " << protocol2->body_as_ResponseAttack()->response_string()->c_str() << std::endl;;
		break;
	}
}

int main()
{
	SetConsoleOutputCP(CP_UTF8);
	setlocale(LC_ALL, "en_US.UTF-8");

	//MonseterTest();
	ProtocolTest();
}