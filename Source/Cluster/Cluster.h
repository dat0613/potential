#pragma once

#include <memory>
#include <vector>
#include <list>
#include <ppl.h>
#include <cassert>
#include <typeindex>
#include <typeinfo>
#include <unordered_map>

class Cluster : public std::enable_shared_from_this<Cluster>
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
	public:
		virtual void Update(int index, float deltaTime) = 0;
	};

	class Node : public std::enable_shared_from_this<Node>
	{
	public:
		template <class Entity>
		class Component : public IComponent
		{
		public:
			Component() : node(nullptr) {}
			Entity& GetEntity(int index) { return entities[index]; }
			const Entity& GetEntityOfOtherIndex(int index) { return entities[index]; }// 주의 : 다른 인덱스 번호의 Entity를 읽어 올때는 const로만 읽어야 함.

			template <class T>
			std::weak_ptr<T> GetComponent() { return node->GetComponent<T>(); }
		private:
			std::shared_ptr<Node> node;
			std::vector<Entity> entities;
		};
	public:

		Node() : cluster(nullptr)
		{

		}

		~Node()
		{

		}

		void Update(float deltaTime)
		{
			int division = 6;// 임시 변수
			int remainder = 3;
			for (auto& component : components)
			{
				concurrency::parallel_for(0, division, [deltaTime, division, remainder, &component](int threadNumber)
				{
					int startCorrection = remainder != 0 ? (remainder > threadNumber ? threadNumber     : remainder) : 0;
					int endCorrection =   remainder != 0 ? (remainder > threadNumber ? threadNumber + 1 : remainder) : 0;

					for (int i = threadNumber * division + startCorrection; i < (threadNumber + 1) * division + endCorrection; i++)
					{
						component->Update(i, deltaTime);
					}
				});
			}
		}

		std::shared_ptr<Cluster>& GetCluster()
		{
			return cluster;
		}

		void SetCluster(const std::shared_ptr<Cluster>& cluster)
		{
			assert(cluster != nullptr);
			this->cluster = cluster;
		}

		template <class T>
		void AddComponent()
		{
			static_assert(std::is_base_of<IComponent, T>::value, "Component class must be derived IComponent interface");
			auto typeIndex = std::type_index(typeid(T));
			assert(componentMap.find(typeIndex) == componentMap.end());

			int vectorIndex = components.size();
			auto component = std::make_shared<T>();
			components.push_back(component);
			componentMap.insert(std::make_pair(typeIndex, vectorIndex));
			return;
		}

		template <class T>
		std::weak_ptr<T> GetComponent()
		{
			static_assert(std::is_base_of<IComponent, T>::value, "Component class must be derived IComponent interface");
			auto typeIndex = std::type_index(typeid(T));
			auto pair = componentMap.find(typeIndex);
			if (pair == componentMap.end())
				return std::weak_ptr<T>();

			return std::static_pointer_cast<T>(components[pair->second]);
		};

	private:
		std::shared_ptr<Cluster> cluster;
		std::vector<std::shared_ptr<IComponent>> components;
		std::unordered_map<std::type_index, int> componentMap; //type_index, components 벡터에 저장된 인덱스 번호
	};

private:

public:
	Cluster() {}

	~Cluster()
	{
		PopAllNode();
	}

	void Update(float deltaTime)
	{
		for (auto& node : nodes)
		{
			node->Update(deltaTime);
		}
	}

	void AddNode(std::shared_ptr<Node>& node)
	{
		assert(node->GetCluster() == nullptr);
		node->SetCluster(shared_from_this());
		nodes.push_back(node);
	}

private:

	void PopAllNode()
	{
		nodes.clear();
	}

private:
	std::vector<std::shared_ptr<Node>> nodes;
};