#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "ImGui/ImGuiLayer.h"
#include "src/Renderer/Shader.h"
#include "src/Renderer/Buffer.h"
#include "Window.h"
#include "LayerStack.h"
namespace Hazel {

	class HAZEL_API Application
	{
	public:
		Application();
		virtual ~Application() = default;

		void OnEvent(Event& e);
		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);
		void Run();

		inline Window& GetWindow() { return *m_Window; }

		inline static Application& Get() { return *s_Instance; }

	private:
		bool OnWindowClose(WindowCloseEvent& e);
		
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;

		unsigned int m_VertexArray;
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;

		static Application* s_Instance;
	};

	// To be defined in CLIENT
	Application* CreateApplication();

}