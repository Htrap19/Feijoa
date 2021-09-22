#pragma once

#include "Fejioa/Core/Base.h"
#include "Fejioa/Core/Window.h"
#include "Fejioa/Events/ApplicationEvent.h"
#include "Fejioa/Core/LayerStack.h"
#include "Fejioa/ImGui/ImGuiLayer.h"

namespace Fejioa
{
	class Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
		
		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		static inline Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }

		void Close();
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

	private:
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		bool m_Minimized = false;
		LayerStack m_LayerStack;
		float m_LastFrameTime = 0.0f;

		static Application* s_Instance;
	};

	// To be defined in the CLIENT
	Application* CreateApplication();
}
