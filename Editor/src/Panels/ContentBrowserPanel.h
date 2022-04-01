#pragma once

#include <src/Core/Log.h>
#include <src/Renderer/Texture.h>

namespace Hazel
{
    class ContentBrowserPanel
    {
    public:
        ContentBrowserPanel();
        ~ContentBrowserPanel() = default;

        void OnImGuiRender();
    private:
        std::filesystem::path m_CurrentDirectory;

        std::shared_ptr<Texture2D> m_DirectoryIcon;
		std::shared_ptr<Texture2D> m_FileIcon;
    };
    
} // namespace 
