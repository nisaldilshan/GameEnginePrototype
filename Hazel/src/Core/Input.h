#pragma once

#include "Base.h"
#include "src/Core/KeyCodes.h"
#include "src/Core/MouseCodes.h"

namespace Hazel {

class HAZEL_API Input
{
public:
    static void Init();
    static void Destroy();
    inline static bool IsKeyPressed(KeyCode key) { return s_Instance->IsKeyPressedImpl(key); }
    inline static bool IsMouseButtonPressed(MouseCode button) { return s_Instance->IsMouseButtonPressedImpl(button); }
    inline static std::pair<float, float> GetMousePosition() { return s_Instance->GetMousePositionImpl(); }
    inline static float GetMouseX() { return s_Instance->GetMouseXImpl(); }
    inline static float GetMouseY() { return s_Instance->GetMouseYImpl(); }

protected:
    virtual bool IsKeyPressedImpl(KeyCode key) = 0;
    virtual bool IsMouseButtonPressedImpl(MouseCode button) = 0;
    virtual std::pair<float, float> GetMousePositionImpl() = 0;
    virtual float GetMouseXImpl() = 0;
    virtual float GetMouseYImpl() = 0;

    static Input* s_Instance;
};

}