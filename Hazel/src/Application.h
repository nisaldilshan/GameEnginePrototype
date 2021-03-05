#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "Core/Timestep.h"
#include "ImGui/ImGuiLayer.h"

#include "Window.h"
#include "LayerStack.h"
namespace Hazel {

	class Application
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
		bool OnWindowResize(WindowResizeEvent& e);
		
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		bool m_Minimized = false;
		LayerStack m_LayerStack;
		float m_LastFrameTime = 0.0f;

		static Application* s_Instance;
	};

	// To be defined in CLIENT
	Application* CreateApplication();

}