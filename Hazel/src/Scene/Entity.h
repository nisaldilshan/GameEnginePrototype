#pragma once

#include <entt/entt.hpp>

namespace Hazel {

	class Scene;

	class Entity
	{
	public:
		Entity() = default;
		Entity(entt::entity handle, Scene* scene);
		Entity(const Entity& other) = default;
		entt::registry& getSceneRegistry();

		template<typename T, typename... Args>
		T& AddComponent(Args&&... args)
		{
			HZ_CORE_ASSERT(!HasComponent<T>(), "Entity already has component!");
			return getSceneRegistry().emplace<T>(m_EntityHandle, std::forward<Args>(args)...);
		}

		template<typename T>
		T& GetComponent()
		{
			HZ_CORE_ASSERT(HasComponent<T>(), "Entity does not have component!");
			return getSceneRegistry().get<T>(m_EntityHandle);
		}

		template<typename T>
		bool HasComponent()
		{
			return getSceneRegistry().all_of<T>(m_EntityHandle);
		}

		template<typename T>
		void RemoveComponent()
		{
			HZ_CORE_ASSERT(HasComponent<T>(), "Entity does not have component!");
			getSceneRegistry().remove<T>(m_EntityHandle);
		}

		operator bool() const { return m_EntityHandle != entt::null; }
	private:
		entt::entity m_EntityHandle{ 0 };
		Scene* m_Scene = nullptr;
	};

}