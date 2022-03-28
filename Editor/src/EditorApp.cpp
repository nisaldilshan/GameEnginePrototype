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
		return new Editor(args);
	}

}
