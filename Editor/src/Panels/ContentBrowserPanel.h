#pragma once

#include <src/Core/Log.h>

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
    };
    
} // namespace 
