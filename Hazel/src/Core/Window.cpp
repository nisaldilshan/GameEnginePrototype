#include <pch.h>
#include "src/Core/Window.h"

#ifdef HZ_PLATFORM_WINDOWS
	#include "src/Platform/Windows/WindowsWindow.h"
#endif

#ifdef HZ_PLATFORM_LINUX
	#include "src/Platform/Linux/LinuxWindow.h"
#endif

namespace Hazel
{
	std::unique_ptr<Window> Window::Create(const WindowProps& props)
	{
	#if defined(HZ_PLATFORM_WINDOWS) 
		return std::make_unique<WindowsWindow>(props);
	#elif defined(HZ_PLATFORM_LINUX)
		return std::make_unique<LinuxWindow>(props);
	#else
		HZ_CORE_ASSERT(false, "Unknown platform!");
		return nullptr;
	#endif
	}

}