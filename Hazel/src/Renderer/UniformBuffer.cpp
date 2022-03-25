#include <pch.h>
#include "UniformBuffer.h"
#include "Renderer.h"
#include "src/Platform/OpenGL/OpenGLUniformBuffer.h"

namespace Hazel {

	std::shared_ptr<UniformBuffer> UniformBuffer::Create(uint32_t size, uint32_t binding)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:    HZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:  return std::make_shared<OpenGLUniformBuffer>(size, binding);
		}

		HZ_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}
