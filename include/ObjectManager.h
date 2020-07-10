#pragma once

#include "EASTL/array.h"
#include "EASTL/queue.h"

#include <cassert>

#include "Types.h"

class ObjectManager
{

private:

	eastl::queue<Object> m_AvailableEntities{};
	eastl::array<ListComponentId, MAX_OBJECTS> m_Signatures{};

	uint32_t m_LivingObjectCount{};

public:

	ObjectManager()
	{
		for (Object object = 0; object < MAX_OBJECTS; ++object)
		{
			m_AvailableEntities.push(object);
		}
	}

	Object CreateObject()
	{
		assert(m_LivingObjectCount < MAX_OBJECTS && "Too many entities in existence.");

		Object id = m_AvailableEntities.front();
		m_AvailableEntities.pop();
		++m_LivingObjectCount;

		return id;
	}

	void DestroyObject(Object obj)
	{
		assert(obj < MAX_OBJECTS && "Object out of range.");

		m_Signatures[obj].reset();
		m_AvailableEntities.push(obj);
		--m_LivingObjectCount;
	}

	void SetSignature(Object obj, ListComponentId signature)
	{
		assert(obj < MAX_OBJECTS && "Object out of range.");

		m_Signatures[obj] = signature;
	}

	ListComponentId GetSignature(Object obj)
	{
		assert(obj < MAX_OBJECTS && "Object out of range.");

		return m_Signatures[obj];
	}
};