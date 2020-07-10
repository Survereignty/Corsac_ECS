#pragma once

#include "ComponentArray.h"
#include "Types.h"

#include <EASTL/unordered_map.h>
#include <EASTL/shared_ptr.h>

class ComponentManager
{
private:
	eastl::unordered_map<const char*, ComponentType> m_ComponentTypes{};
	eastl::unordered_map<const char*, eastl::shared_ptr<IComponentArray>> m_ComponentArrays{};
	ComponentType m_NextComponentType{};

	template<typename T>
	eastl::shared_ptr<ComponentArray<T>> GetComponentArray()
	{
		const char* typeName = typeid(T).name();

		assert(m_ComponentTypes.find(typeName) != m_ComponentTypes.end() && "Component not registered before use.");

		return eastl::static_pointer_cast<ComponentArray<T>>(m_ComponentArrays[typeName]);
	}

public:
	template<typename T>
	void RegisterComponent()
	{
		const char* typeName = typeid(T).name();

		assert(m_ComponentTypes.find(typeName) == m_ComponentTypes.end() && "Registering component type more than once.");

		m_ComponentTypes.insert({ typeName, m_NextComponentType });
		m_ComponentArrays.insert({ typeName, eastl::make_shared<ComponentArray<T>>() });

		++m_NextComponentType;
	}

	template<typename T>
	ComponentType GetComponentType()
	{
		const char* typeName = typeid(T).name();

		assert(m_ComponentTypes.find(typeName) != m_ComponentTypes.end() && "Component not registered before use.");

		return m_ComponentTypes[typeName];
	}

	template<typename T>
	void AddComponent(Object obj, T component)
	{
		GetComponentArray<T>()->InsertData(obj, component);
	}

	template<typename T>
	void RemoveComponent(Object obj)
	{
		GetComponentArray<T>()->RemoveData(obj);
	}

	template<typename T>
	T& GetComponent(Object obj)
	{
		return GetComponentArray<T>()->GetData(obj);
	}

	void ObjectDestroyed(Object obj)
	{
		for (auto const& pair : m_ComponentArrays)
		{
			auto const& component = pair.second;
			component->ObjectDestroyed(obj);
		}
	}
};