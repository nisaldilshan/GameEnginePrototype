#include <pch.h>
#include "src/Core/Window.h"

#ifdef HZ_PLATFORM_WINDOWS
	#include "src/Platform/Windows/WindowsWindow.h"
#endif

namespace Hazel
{
	std::unique_ptr<Window> Window::Create(const WindowProps& props)
	{
	#ifdef HZ_PLATFORM_WINDOWS
		return std::make_unique<WindowsWindow>(props);
	#else
		HZ_CORE_ASSERT(false, "Unknown platform!");
		return nullptr;
	#endif
	}

}