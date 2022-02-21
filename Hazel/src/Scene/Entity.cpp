#include "Entity.h"
#include "Scene.h"
#include <pch.h>

namespace Hazel
{

	Entity::Entity(entt::entity handle, Scene* scene)
	    : m_EntityHandle(handle)
	    , m_Scene(scene)
	{
	}

} // namespace Hazel