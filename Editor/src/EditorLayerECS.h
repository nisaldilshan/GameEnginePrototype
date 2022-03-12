#pragma once

#include <Hazel.h>
#include "Panels/SceneHierarchyPanel.h"

namespace Hazel {

	class EditorLayer : public Layer
	{
	public:
		EditorLayer();
		virtual ~EditorLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		void OnUpdate(Timestep ts) override;
		virtual void OnImGuiRender() override;
		void OnEvent(Event& e) override;
		
	private:
		bool OnKeyPressed(KeyPressedEvent& e);
		void NewScene();
		void OpenScene();
		void SaveSceneAs();

		// Temp
		std::shared_ptr<VertexArray> m_SquareVA;
		std::shared_ptr<Shader> m_FlatColorShader;
		std::shared_ptr<Framebuffer> m_Framebuffer;

		std::shared_ptr<Scene> m_ActiveScene;

		EditorCamera m_EditorCamera;


		bool m_ViewportFocused = false, m_ViewportHovered = false;
		glm::vec2 m_ViewportSize = { 0.0f, 0.0f };

		SceneHierarchyPanel m_SceneHierarchyPanel;

		int m_GizmoType = -1;
	}; 
}
