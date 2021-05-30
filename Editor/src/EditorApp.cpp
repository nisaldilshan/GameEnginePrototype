#include <Hazel.h>
#include <src/Core/EntryPoint.h>

#include <imgui.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "EditorLayer.h"

namespace Hazel {
	class Editor : public Application
	{
	public:
		Editor()
			: Application("Editor Prototype")
		{
			//PushLayer(new ExampleLayer());
			PushLayer(new EditorLayer());
		}

		~Editor()
		{

		}

	};

	Application* CreateApplication()
	{
		return new Editor();
	}

}
