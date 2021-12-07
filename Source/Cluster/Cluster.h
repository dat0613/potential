#pragma once

#include <memory>
#include <list>
#include <future>
#include <iostream>
#include <ppl.h>
#include "GameObject.h"

class Cluster
{
public:

	// IComponent 인터페이스를 상속받는 컴포넌트들 중 같은 종류들은 모두 배열로 관리
	// 객체가 데이터를 갖는것이 아닌, 선형적인 데이터들과 함수들로 객체를 추상화
	// 다른 컴포넌트의 값을 읽어올 때는 무조건 read-only
	// 다른 컴포넌트의 값을 변경 할때는 무조건 event 방식
	// event로 전달한 값은 다음번 Update루프의 맨 처음에 적용됨
	// 기존 OOP방식의 Update에서도 다른 객체의 컴포넌트의 값을 변경 했을 때 
	// 이미 변경되는 객체의 Update가 끝난 후 라면 다음 루프에 변경된 값으로 Update가 돌기 때문에 문제는 없을듯

	class IComponent
	{
		virtual void Update(int index, float deltaTime) = 0;
	};

	template <class Entity>
	class Component : public IComponent
	{
	private:
		//Cluster& cluster;

	public:
		//Component(Cluster& cluster) : cluster(cluster) {}
		std::vector<Entity> entities;
	};
private:


	class Node : public std::enable_shared_from_this<Node>
	{
	public:
		Node(int identity) : identity(identity)
		{

		}

		~Node()
		{

		}

		void Update()
		{

		}

		int GetIdentity() { return identity; }

	private:
		int identity;
	};

public:
	Cluster(int nodeCount) : nodeCount(nodeCount), nodeIdentityGenerator(0)
	{
		for (int i = 0; i < nodeCount; i++)
		{
			AddNode(nodeIdentityGenerator++);
		}
	}

	~Cluster()
	{
		PopAllNode();
	}

	void Update()
	{
		concurrency::parallel_for
		(0, nodeCount, [this](int index)
			{
				nodes[index]->Update();
			}
		);
	}

	template <class T>
	bool AddComponent()
	{
		auto component = std::make_shared<T>();
		components.push_back(component);

		return true;
	}

private:

	bool AddNode(int identity)
	{
		if (nodeMap.find(identity) != nodeMap.end())
			return false;

		auto node = std::make_shared<Node>(identity);
		nodes.push_back(node);
		nodeMap.insert(std::make_pair(identity, node));
	}

	void PopAllNode()
	{
		for (int i = 0; i < nodeCount; i++)
		{
			auto& node = nodes.back();
			auto identity = node->GetIdentity();
			nodeMap.erase(identity);
			nodes.pop_back();
		}
	}

private:
	std::vector<std::shared_ptr<Node>> nodes;// 빠른 순회를 위한 vector
	std::map<int, std::shared_ptr<Node>> nodeMap;// 빠른 검색을 위한 map
	std::vector<std::shared_ptr<IComponent>> components;
	int nodeCount;
	int nodeIdentityGenerator;
};