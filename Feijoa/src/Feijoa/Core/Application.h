#pragma once

#include "Feijoa/Core/Base.h"
#include "Feijoa/Core/Window.h"
#include "Feijoa/Events/ApplicationEvent.h"
#include "Feijoa/Core/LayerStack.h"
#include "Feijoa/ImGui/ImGuiLayer.h"

namespace Feijoa
{
	class Application
	{
	public:
		Application(const std::string& name = "Feijoa App");
		virtual ~Application();

		void Run();
		
		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		static inline Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }

		void Close();

		inline ImGuiLayer* GetImGuiLayer() { return m_ImGuiLayer; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

	private:
		Scope<Window> m_Window;
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
