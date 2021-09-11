#pragma once

#include "Fejioa/Core/Layer.h"
#include "Fejioa/Events/MouseEvent.h"
#include "Fejioa/Events/KeyEvent.h"
#include "Fejioa/Events/ApplicationEvent.h"

namespace Fejioa
{
	class ImGuiLayer : public Layer
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