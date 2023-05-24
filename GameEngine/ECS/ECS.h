#pragma once
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

class Component;
class Entity;
class Manager;


inline std::size_t getComponentTypeID()
{
	static std::size_t lastID = 0;
	return lastID++;
}

template <typename T>
inline std::size_t getComponentTypeID() noexcept
{
	static std::size_t typeID = getComponentTypeID();
	return typeID;
}

constexpr std::size_t maxComponents = 32;

class Component 
{
public:
	Entity* entity;
	virtual void init() {}
	virtual void update() {}
	virtual void draw() {}
	~Component() {}
};

class Entity
{
private:
	std::vector<std::unique_ptr<Component>> components;
	std::array<Component*, maxComponents> componentArray;
	std::bitset<maxComponents> componentBitSet;
	bool active = true;

public:
	void update()
	{
		for (auto& component : components)
		{
			component->update();
		}
	}

	void draw()
	{
		for (auto& component : components)
		{
			component->draw();
		}
	}

	void destroy()
	{
		active = false;
	}

	bool isActive () const
	{
		return active;
	}

	template <typename T> 
	bool hasComponent() const
	{
		return componentBitSet[getComponentTypeID<T>()];
	}

	template <typename T, typename... TArgs>
	T& addComponent(TArgs&&... mArgs)
	{
		T* newComponent(new T(std::forward<TArgs>(mArgs)...));
		newComponent->entity = this;
		std::unique_ptr<Component> uPtr{ newComponent };
		components.emplace_back(std::move(uPtr));
		componentArray[getComponentTypeID<T>()] = newComponent;
		componentBitSet[getComponentTypeID<T>()] = true;
		newComponent->init();
		return *newComponent;
	}

	template<typename T>
	T& getComponent() const
	{
		auto ptr(componentArray[getComponentTypeID<T>()]);
		return *static_cast<T*>(ptr);
	}

};

class Manager 
{
private:
	std::vector<std::unique_ptr<Entity>> entities;

public:
	void update()
	{
		for (auto& entity : entities)
		{
			entity->update();
		}
	}

	void draw()
	{
		for (auto& entity : entities)
		{
			entity->draw();
		}
	}

	void refresh()
	{
		entities.erase(std::remove_if(std::begin(entities), std::end(entities),
			[](const std::unique_ptr<Entity>& mEntity)
			{
				return !mEntity->isActive();
			}),
			std::end(entities));
	}

	Entity& addEntity()
	{
		Entity* entity = new Entity();
		std::unique_ptr<Entity> uPtr{ entity };
		entities.emplace_back(std::move(uPtr));
		return *entity;
	}
};