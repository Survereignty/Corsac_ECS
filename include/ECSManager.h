#pragma once

#include "ComponentManager.h"
#include "ObjectManager.h"
#include "EventManager.h"
#include "SystemManager.h"
#include "Types.h"

#include <EASTL/unique_ptr.h>

class ECSManager
{
private:
	eastl::unique_ptr<ComponentManager> m_ComponentManager;
	eastl::unique_ptr<ObjectManager>	m_ObjectManager;
	eastl::unique_ptr<EventManager>		m_EventManager;
	eastl::unique_ptr<SystemManager>	m_SystemManager;
public:
	void Init()
	{
		m_ComponentManager	= eastl::make_unique<ComponentManager>();
		m_ObjectManager		= eastl::make_unique<ObjectManager>();
		m_EventManager		= eastl::make_unique<EventManager>();
		m_SystemManager		= eastl::make_unique<SystemManager>();
	}

	Object CreateObject()
	{
		return m_ObjectManager->CreateObject();
	}

	void DestroyObject(Object obj)
	{
		m_ObjectManager->DestroyObject(obj);
		m_ComponentManager->ObjectDestroyed(obj);
		m_SystemManager->ObjectDestroyed(obj);
	}

	template<typename T>
	void RegisterComponent()
	{
		m_ComponentManager->RegisterComponent<T>();
	}


	template<typename T>
	void AddComponent(Object obj, T component)
	{
		component.GameObject = obj;
		m_ComponentManager->AddComponent<T>(obj, component);

		auto signature = m_ObjectManager->GetSignature(obj);
		signature.set(m_ComponentManager->GetComponentType<T>(), true);
		m_ObjectManager->SetSignature(obj, signature);

		m_SystemManager->ObjectSignatureChanged(obj, signature);
	}

	template<typename T>
	void RemoveComponent(Object obj)
	{
		m_ComponentManager->RemoveComponent<T>(obj);

		auto signature = m_ObjectManager->GetSignature(obj);
		signature.set(m_ComponentManager->GetComponentType<T>(), false);
		m_ObjectManager->SetSignature(obj, signature);

		m_SystemManager->ObjectSignatureChanged(obj, signature);
	}

	template<typename T>
	T& GetComponent(Object obj)
	{
		return m_ComponentManager->GetComponent<T>(obj);
	}

	template<typename T>
	ComponentType GetComponentType()
	{
		return m_ComponentManager->GetComponentType<T>();
	}

	template<typename T>
	eastl::shared_ptr<T> RegisterSystem()
	{
		return m_SystemManager->RegisterSystem<T>();
	}

	template<typename T>
	void SetSystemSignature(ListComponentId signature)
	{
		m_SystemManager->SetSignature<T>(signature);
	}

	void AddEventListener(EventId eventId, eastl::function<void(Event&)> const& listener)
	{
		m_EventManager->AddListener(eventId, listener);
	}

	void SendEvent(Event& event)
	{
		m_EventManager->SendEvent(event);
	}

	void SendEvent(EventId eventId)
	{
		m_EventManager->SendEvent(eventId);
	}
};

