#pragma once

#include "src/Core/Layer.h"

#include "src/Events/ApplicationEvent.h"
#include "src/Events/KeyEvent.h"
#include "src/Events/MouseEvent.h"

namespace Hazel {

	class HAZEL_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		void Begin();
		void End();
	private:
		float m_Time = 0.0f;
	};

}