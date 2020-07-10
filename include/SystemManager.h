#pragma once

#include "System.h"
#include "Types.h"

#include <cassert>

#include <EASTL/unordered_map.h>
#include <EASTL/shared_ptr.h>

///////////////////////////////////////////////////
//
// Менеджер управления системами
//
// Регистрирует системы и устанавливает им сигнатурные типы компонентов
//
///////////////////////////////////////////////////
class SystemManager
{
private:
	// Карта сигнатурных компонентов
	eastl::unordered_map<const char*, ListComponentId> m_Signatures{};
	// Карта существующих систем
	eastl::unordered_map<const char*, eastl::shared_ptr<CRSC_System>> m_Systems{};
public:
	// Регистрация системы

	template<typename T>
	eastl::shared_ptr<T> RegisterSystem()
	{
		const char* typeName = typeid(T).name();

		assert(m_Systems.find(typeName) == m_Systems.end() && "Registering system more than once.");

		auto system = eastl::make_shared<T>();
		m_Systems.insert({ typeName, system });
		return system;
	}

	// Установка сигнатурного компонента
	template<typename T>
	void SetSignature(ListComponentId signature)
	{
		const char* typeName = typeid(T).name();

		assert(m_Systems.find(typeName) != m_Systems.end() && "System used before registered.");

		m_Signatures.insert({ typeName, signature });
	}

	// Удалить сущность из системы
	void ObjectDestroyed(Object obj)
	{
		for (auto const& pair : m_Systems)
		{
			auto const& system = pair.second;
			system->Objects.erase(obj);
		}
	}

	void ObjectSignatureChanged(Object obj, ListComponentId objectSignature)
	{
		for (auto const& pair : m_Systems)
		{
			auto const& type = pair.first;
			auto const& system = pair.second;
			auto const& systemSignature = m_Signatures[type];

			if ((objectSignature & systemSignature) == systemSignature)
			{
				system->Objects.insert(obj);
			}
			else
			{
				system->Objects.erase(obj);
			}
		}
	}
};