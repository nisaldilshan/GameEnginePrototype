#include "Scene.h"
#include <pch.h>

#include "Components.h"
#include "src/Renderer/Renderer2D.h"

#include <glm/glm.hpp>

namespace Hazel
{
	Scene::Scene() {}

	Scene::~Scene() {}

	Entity Scene::CreateEntity(const std::string& name)
	{
		Entity entity{m_Registry.create(), this};
		entity.AddComponent<TransformComponent>();
		auto& tag = entity.AddComponent<TagComponent>();
		tag.Tag = name.empty() ? "Entity" : name;
		return entity;
	}
	
	void Scene::DestroyEntity(Entity entity)
	{
		m_Registry.destroy(entity);
	}
	
	void Scene::OnUpdateEditor(Timestep ts, EditorCamera& camera)
	{
		Hazel::Renderer2D::BeginScene(camera);

			auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
			for (auto entity : group)
			{
				auto& transform = group.get<TransformComponent>(entity);
				auto& sprite = group.get<SpriteRendererComponent>(entity);

				Renderer2D::DrawSprite(transform.GetTransform(), sprite, (int)entity);
			}

		Renderer2D::EndScene();
	}

	void Scene::OnUpdateRuntime(Timestep ts)
	{
		// Update scripts
		{
			m_Registry.view<NativeScriptComponent>().each([=](auto entity, auto& nsc)
			{
				// TODO: Move to Scene::OnScenePlay
				if (!nsc.Instance)
				{
					nsc.Instance = nsc.InstantiateFunction();
					nsc.Instance->m_Entity = { entity, this };
					nsc.Instance->OnCreate();
				}

				nsc.Instance->OnUpdate(ts);
			});
		}

		// Render sprites
		Camera* mainCamera = nullptr;
		glm::mat4 mainCameraTransform;

		{
			auto view = m_Registry.view<CameraComponent, TransformComponent>();
			for (auto entity : view)
			{
				auto [transform, camera] = view.get<TransformComponent, CameraComponent>(entity);
				if (camera.Primary)
				{
					mainCamera = &camera.Camera;
					mainCameraTransform = transform.GetTransform();
					break;
				}
			}
		}

		if (mainCamera)
		{
			Hazel::Renderer2D::BeginScene(*mainCamera, mainCameraTransform);

			auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
			for (auto entity : group)
			{
				auto& transform = group.get<TransformComponent>(entity);
				auto& sprite = group.get<SpriteRendererComponent>(entity);

				Renderer2D::DrawSprite(transform.GetTransform(), sprite, (int)entity);
			}

			Renderer2D::EndScene();
		}
	}
	
	void Scene::OnViewportResize(uint32_t width, uint32_t height)
	{
		m_ViewportWidth = width;
		m_ViewportHeight = height;

		// resize cameras 
		auto view = m_Registry.view<CameraComponent>();
		for (auto entity : view)
		{
			auto& cameraComponent = view.get<CameraComponent>(entity);
			if (!cameraComponent.FixedAspectRatio)
			{
				cameraComponent.Camera.SetViewportSize(m_ViewportWidth, m_ViewportHeight);
			}
		}
	}
	
	Entity Scene::GetPrimaryCameraEntity()
	{
		auto view = m_Registry.view<CameraComponent>();
		for (auto entity : view)
		{
			auto camera = view.get<CameraComponent>(entity);
			if (camera.Primary)
			{
				return Entity{entity, this};
			}
		}

		return {};
	}
	
	template<typename T>
	void Scene::OnComponentAdded(Entity entity, T& component)
	{
		assert(false);
	}

	template <>
	void Scene::OnComponentAdded<TransformComponent>(Entity entity, TransformComponent& component)
	{

	}

	template <>
	void Scene::OnComponentAdded<CameraComponent>(Entity entity, CameraComponent& component)
	{
		if (m_ViewportWidth > 0 && m_ViewportHeight > 0)
			component.Camera.SetViewportSize(m_ViewportWidth, m_ViewportHeight);
	}

	template <>
	void Scene::OnComponentAdded<TagComponent>(Entity entity, TagComponent& component)
	{

	}

	template <>
	void Scene::OnComponentAdded<SpriteRendererComponent>(Entity entity, SpriteRendererComponent& component)
	{

	}

	template <>
	void Scene::OnComponentAdded<NativeScriptComponent>(Entity entity, NativeScriptComponent& component)
	{

	}

} // namespace Hazel