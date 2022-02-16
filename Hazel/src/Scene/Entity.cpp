#include <pch.h>
#include "Entity.h"
#include "Scene.h"

namespace Hazel {

	Entity::Entity(entt::entity handle, Scene* scene)
		: m_EntityHandle(handle), m_Scene(scene)
	{
	}
	
	entt::registry& Entity::getSceneRegistry() 
	{
		return m_Scene->m_Registry;
	}

}