#pragma once

#include "Fejioa/Layer.h"
#include "Fejioa/Events/MouseEvent.h"
#include "Fejioa/Events/KeyEvent.h"
#include "Fejioa/Events/ApplicationEvent.h"

namespace Fejioa
{
	class FEJIOA_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();

	private:
		float m_Time = 0.0f;
	};
}