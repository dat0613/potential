#pragma once

#include <memory>
#include <list>
#include <future>
#include <iostream>
#include <ppl.h>
#include "GameObject.h"

class Cluster
{
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
	int nodeCount;
	int nodeIdentityGenerator;
};