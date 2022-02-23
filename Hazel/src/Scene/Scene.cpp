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

	void Scene::OnUpdate(Timestep ts)
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
		glm::mat4* mainCameraTransform = nullptr;

		{
			auto view = m_Registry.view<CameraComponent, TransformComponent>();
			for (auto entity : view)
			{
				auto [transform, camera] = view.get<TransformComponent, CameraComponent>(entity);
				if (camera.Primary)
				{
					mainCamera = &camera.Camera;
					mainCameraTransform = &transform.Transform;
					break;
				}
			}
		}

		if (mainCamera)
		{
			Hazel::Renderer2D::BeginScene(*mainCamera, *mainCameraTransform);

			auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
			for (auto entity : group)
			{
				auto& transform = group.get<TransformComponent>(entity);
				auto& sprite = group.get<SpriteRendererComponent>(entity);

				Renderer2D::DrawQuad(transform, sprite.Color);
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

} // namespace Hazel