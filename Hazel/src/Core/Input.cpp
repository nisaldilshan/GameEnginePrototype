#include <pch.h>
#include "Input.h"

#ifdef HZ_PLATFORM_WINDOWS
	#include "src/Platform/Windows/WindowsInput.h"
#endif

namespace Hazel {

	std::unique_ptr<Input> Input::s_Instance = Input::Create();

	std::unique_ptr<Input> Input::Create()
	{
	#ifdef HZ_PLATFORM_WINDOWS
		return std::make_unique<WindowsInput>();
	#else
		HZ_CORE_ASSERT(false, "Unknown platform!");
		return nullptr;
	#endif
	}
} 