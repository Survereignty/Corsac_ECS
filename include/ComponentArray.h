#pragma once

#include "Types.h"

#include <EASTL/array.h>
#include <EASTL/unordered_map.h>

#include <cassert>

class IComponentArray
{
public:
	virtual ~IComponentArray() = default;
	virtual void ObjectDestroyed(Object Object) = 0;
};


template<typename T>
class ComponentArray : public IComponentArray
{
private:
	eastl::array<T, MAX_OBJECTS> m_ComponentArray{};
	eastl::unordered_map<Object, size_t> m_ObjectToIndexMap{};
	eastl::unordered_map<size_t, Object> m_IndexToObjectMap{};
	size_t mSize{};

public:
	void InsertData(Object obj, T component)
	{
		assert(m_ObjectToIndexMap.find(obj) == m_ObjectToIndexMap.end() && "Component added to same Object more than once.");

		size_t newIndex = mSize;
		m_ObjectToIndexMap[Object] = newIndex;
		m_IndexToObjectMap[newIndex] = obj;
		m_ComponentArray[newIndex] = component;
		++mSize;
	}

	void RemoveData(Object obj)
	{
		assert(m_ObjectToIndexMap.find(obj) != m_ObjectToIndexMap.end() && "Removing non-existent component.");

		size_t indexOfRemovedObject = m_ObjectToIndexMap[obj];
		size_t indexOfLastElement = mSize - 1;
		m_ComponentArray[indexOfRemovedObject] = m_ComponentArray[indexOfLastElement];

		Object ObjectOfLastElement = m_IndexToObjectMap[indexOfLastElement];
		m_ObjectToIndexMap[ObjectOfLastElement] = indexOfRemovedObject;
		m_IndexToObjectMap[indexOfRemovedObject] = ObjectOfLastElement;

		m_ObjectToIndexMap.erase(obj);
		m_IndexToObjectMap.erase(indexOfLastElement);

		--mSize;
	}

	T& GetData(Object obj)
	{
		assert(m_ObjectToIndexMap.find(obj) != m_ObjectToIndexMap.end() && "Retrieving non-existent component.");

		return m_ComponentArray[m_ObjectToIndexMap[obj]];
	}

	void ObjectDestroyed(Object obj) override
	{
		if (m_ObjectToIndexMap.find(obj) != m_ObjectToIndexMap.end())
		{
			RemoveData(obj);
		}
	}
};
