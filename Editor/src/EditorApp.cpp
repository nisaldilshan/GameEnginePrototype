#include <Hazel.h>
#include <src/Core/EntryPoint.h>

#include "EditorLayer.h"

namespace Hazel {
	class Editor : public Application
	{
	public:
		Editor(ApplicationCommandLineArgs args)
			: Application("Editor Prototype", args)
		{
			PushLayer(new EditorLayer());
		}

		~Editor()
		{
		}
	};

	Application* CreateApplication(ApplicationCommandLineArgs args)
	{
		std::cout << "sizeof(EditorLayer)" <<sizeof(EditorLayer) << std::endl;
		//std::cout << "sizeof(ContentBrowserPanel)" <<sizeof(ContentBrowserPanel) << std::endl;
		//std::cout << "sizeof(SceneHierarchyPanel)" <<sizeof(SceneHierarchyPanel) << std::endl;
		std::cout << "sizeof(Entity)" <<sizeof(Entity) << std::endl;
		std::cout << "sizeof(EditorCamera)" <<sizeof(EditorCamera) << std::endl;
		return new Editor(args);
	}

}
