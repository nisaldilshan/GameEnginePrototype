#include "pch.h"
#include "RenderCommand.h"

#include "src/Platform/OpenGL/OpenGLRendererAPI.h"

namespace Hazel {

	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI();

} 