#pragma once

#include "Types.h"

#include <EASTL/unordered_map.h>
#include <EASTL/any.h>

///////////////////////////////////////////////////
//
// Класс события
//
///////////////////////////////////////////////////
class Event
{
private:
	EventId m_Type{};
	eastl::unordered_map<EventId, eastl::any> m_Data{};

public:
	Event() = delete;

	explicit Event(EventId type)
		: m_Type(type)
	{}

	template<typename T>
	void SetParam(EventId id, T value)
	{
		m_Data[id] = value;
	}

	template<typename T>
	T GetParam(EventId id)
	{
		return eastl::any_cast<T>(m_Data[id]);
	}

	EventId GetType() const
	{
		return m_Type;
	}
};
