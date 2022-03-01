#pragma once

#include <src/Core/Log.h>
#include <src/Scene/Scene.h>
#include <src/Scene/Entity.h>

namespace Hazel
{
    class SceneHierarchyPanel
    {
    public:
        SceneHierarchyPanel() = default;
        SceneHierarchyPanel(const std::shared_ptr<Scene> scene);
        ~SceneHierarchyPanel() = default;

        void SetContext(const std::shared_ptr<Scene> scene);
        void OnImGuiRender();
    private:
        void DrawEntityNode(Entity entity);
        void DrawComponents(Entity entity);
        
        std::shared_ptr<Scene> m_Context;
        Entity m_SelectionContext;

        friend class Scene;
    };
    
} // namespace 
