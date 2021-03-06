#include "pch.h"
#include "RenderCommand.h"

#include "src/Platform/OpenGL/OpenGLRendererAPI.h"

namespace Hazel {

	std::unique_ptr<RendererAPI> RenderCommand::s_RendererAPI = std::make_unique<OpenGLRendererAPI>();

} 