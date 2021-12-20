#pragma once

#include <memory>
#include <vector>
#include <list>
#include <ppl.h>
#include <cassert>
#include <typeindex>
#include <typeinfo>
#include <unordered_map>
#include <optional>

#include <SFML/Graphics.hpp>

class Cluster : public std::enable_shared_from_this<Cluster>
{
public:
	static constexpr int ParallelScale = 6;
	static constexpr int DefaultAllocationSize = 10000;

	// IComponent 인터페이스를 상속받는 컴포넌트들 중 같은 종류들은 모두 배열로 관리
	// 객체가 데이터를 갖는것이 아닌, 선형적인 데이터들과 함수들로 객체를 추상화
	// 다른 컴포넌트의 값을 읽어올 때는 무조건 read-only
	// 다른 컴포넌트의 값을 변경 할때는 무조건 event 방식
	// event로 전달한 값은 다음번 Update루프의 맨 처음에 적용됨
	// 기존 OOP방식의 Update에서도 다른 객체의 컴포넌트의 값을 변경 했을 때 
	// 이미 변경되는 객체의 Update가 끝난 후 라면 다음 루프에 변경된 값으로 Update가 돌기 때문에 문제는 없을듯

	class Node;

	class IComponent
	{
	public:
		virtual void Update(float deltaTime) = 0;
		virtual void Initialize(void* parameter) = 0;
		virtual void Draw(sf::RenderWindow& window) {}
		virtual void SetNode(const std::weak_ptr<Node>& node) {}
		virtual void SetIndex(int index) {}
		virtual int GetIndex() const { return -1; }
		virtual bool IsActive() const { return false; }
	};

private:
	class IComponentWrapper
	{
		virtual void Push(void* parameter) = 0;
	};

public:
	class INode
	{
	public:
		virtual void Update(float deltaTime) {}
		virtual void Draw(sf::RenderWindow& window) {}
		virtual void SetCluster(const std::shared_ptr<Cluster>& cluster) {}
		virtual std::shared_ptr<Cluster> GetCluster() { return nullptr; }
	};

	class Node : public INode, public std::enable_shared_from_this<Node>
	{
	public:
		
		class Component : public IComponent
		{
		public:
			Component() : isActive(false), index(-1) {}

			template <class T>
			std::weak_ptr<T> GetComponent() { return node.lock()->GetComponent<T>(GetIndex()); }// Component는 부모 Node의 컨테이너에 shared_ptr로 잡혀있기 때문에, 자신이 살아있다면 Node는 무조건 살아있음.
			template <class T>
			std::weak_ptr<T> GetOtherComponent(int index) { return node.lock()->GetComponent<T>(GetIndex(index)); }// Component는 부모 Node의 컨테이너에 shared_ptr로 잡혀있기 때문에, 자신이 살아있다면 Node는 무조건 살아있음.
			void SetNode(const std::weak_ptr<Node>& node) override { this->node = node; };// 부모 Node와 상호 참조를 예방하기 위해 weak_ptr사용
			void SetIndex(int index) override { this->index = index; }
			int GetIndex() const override { return index; }
			bool IsActive() const override { return isActive; }

		private:
			std::weak_ptr<Node> node;
			bool isActive;
			int index;
		};

	private:

		template <class T>
		class ComponentWrapper : public IComponentWrapper
		{
		public:
			void Push(void* parameter) override
			{
				auto comp = std::make_shared<T>();
				comp.Initialize(parameter);
				components.push_back(comp);
			}

			void GetComponent(int index) override
			{
				return components[index];// 인덱스 검사 필요
			}

			void Update(float deltaTime) override
			{
				int entityCount = components.size();
				if (entityCount == 0)
					continue;

				int division = entityCount / ParallelScale;
				int remainder = entityCount % ParallelScale;

				concurrency::parallel_for(0, ParallelScale, [deltaTime, division, remainder, &components](int threadNumber)
					{
						int startCorrection = remainder != 0 ? (remainder > threadNumber ? threadNumber : remainder) : 0;
						int endCorrection = remainder != 0 ? (remainder > threadNumber ? threadNumber + 1 : remainder) : 0;

						for (int i = threadNumber * division + startCorrection; i < (threadNumber + 1) * division + endCorrection; i++)
						{
							if (!components[i]->IsActive())
								continue;

							components[i]->Update(deltaTime);
						}
					});

			}

		private:
			std::vector<std::shared_ptr<T>> components;
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
			for (auto& component : components)
			{
				component
			}
		}

		void Draw(sf::RenderWindow& window)
		{
			for (auto& component : components)
			{
				int entityCount = component.size();

				for (int i = 0; i < entityCount; i++)
				{
					if (!component[i]->IsActive())
						continue;

					component[i]->Draw(window);
				}
			}
		}

		std::shared_ptr<Cluster> GetCluster() override
		{
			return cluster;
		}

		void SetCluster(const std::shared_ptr<Cluster>& cluster) override
		{
			assert(cluster != nullptr);
			this->cluster = cluster;
		}

		template <class T>
		int AddObject()
		{

		}

		template <class T>
		void AddComponent()
		{
			static_assert(std::is_base_of<IComponent, T>::value, "Component class must be derived IComponent interface");
			assert(componentMap.find(typeIndex) == componentMap.end());

			int vectorIndex = components.size();
			std::vector<std::shared_ptr<IComponent>> entities;
			entities.reserve(DefaultAllocationSize);
			components.push_back(entities);
			componentMap.insert(std::make_pair(std::type_index(typeid(T)), vectorIndex));
			return;
		}

		template <class T>
		std::weak_ptr<T> GetComponent(int index)
		{
			static_assert(std::is_base_of<IComponent, T>::value, "Component class must be derived IComponent interface");

			auto typeIndex = std::type_index(typeid(T));
			auto pair = componentMap.find(typeIndex);
			if (pair == componentMap.end())
				return std::weak_ptr<T>();

			return std::static_pointer_cast<T>(components[pair->second][index]);
		};

	protected:
		std::shared_ptr<Cluster> cluster;
		std::vector<IComponentWrapper> componentWrappers;
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

	void Draw(sf::RenderWindow& window)
	{
		for (auto& node : nodes)
		{
			node->Draw(window);
		}
	}

	void AddNode(std::shared_ptr<INode> node)
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
	std::vector<std::shared_ptr<INode>> nodes;
};