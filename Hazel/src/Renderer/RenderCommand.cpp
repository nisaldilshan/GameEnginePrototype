#include <pch.h>
#include "RenderCommand.h"

namespace Hazel {

	std::unique_ptr<RendererAPI> RenderCommand::s_RendererAPI = RendererAPI::Create();

} 