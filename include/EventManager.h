#pragma once

#include "Event.h"
#include "Types.h"

#include <EASTL/list.h>
#include <EASTL/unordered_map.h>

///////////////////////////////////////////////////
//
// Менеджер управления событиями
//
// Регистрирует события
//
///////////////////////////////////////////////////
class EventManager
{
private:
	// Карта событий
	eastl::unordered_map<EventId, eastl::list<eastl::function<void(Event&)>>> listeners;
public:
	// Добавить прослушку события изменения
	void AddListener(EventId eventId, eastl::function<void(Event&)> const& listener)
	{
		listeners[eventId].push_back(listener);
	}
	// Вызвать событие
	void SendEvent(Event& event)
	{
		uint32_t type = event.GetType();

		for (auto const& listener : listeners[type])
		{
			listener(event);
		}
	}
	// Вызвать событие
	void SendEvent(EventId eventId)
	{
		Event event(eventId);

		for (auto const& listener : listeners[eventId])
		{
			listener(event);
		}
	}
};