#include "pch.h"
#include "FrameBuffer.h"

#include "src/Renderer/Renderer.h"

#include "src/Platform/OpenGL/OpenGLFrameBuffer.h"

namespace Hazel {

	std::shared_ptr<Framebuffer> Framebuffer::Create(const FramebufferSpecification& spec)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:    HZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:  return std::make_shared<OpenGLFramebuffer>(spec);
		}

		HZ_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}