#pragma once

#include "Feijoa/Core/Layer.h"
#include "Feijoa/Events/MouseEvent.h"
#include "Feijoa/Events/KeyEvent.h"
#include "Feijoa/Events/ApplicationEvent.h"

namespace Feijoa
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