#pragma once

#include <Feijoa.h>
#include "Panels/SceneHierarchyPanel.h"
#include "Feijoa/Renderer/EditorCamera.h"

namespace Feijoa
{
	class SellowianaLayer : public Layer // Sellowiana EditorLayer
	{
	public:
		SellowianaLayer();
		virtual ~SellowianaLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		virtual void OnUpdate(Feijoa::Timestep ts) override;
		virtual void OnImGuiRender() override;
		virtual void OnEvent(Feijoa::Event& e) override;

	private:
		bool OnKeyPressed(KeyPressedEvent& e);
		bool OnMouseButtonPressed(MouseButtonEvent& e);

		void NewScene();
		void OpenScene();
		void SaveSceneAs();

	private:
		OrthographicCameraController m_CameraController;

		Ref<Framebuffer> m_FrameBuffer;
		Ref<Texture2D> m_CheckerBoardTexture;

		Ref<Scene> m_ActiveScene;
		Entity m_SquareEntity;
		Entity m_CameraEntity;
		Entity m_SecondCamera;

		Entity m_HoveredEntity;

		EditorCamera m_EditorCamera;

		bool m_PrimaryCamera = true;
		bool m_ViewportFocused = false, m_ViewportHovered = false;
		glm::vec2 m_ViewportSize = { 0.0f, 0.0f };
		glm::vec2 m_ViewportBounds[2];
		glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };

		// Panels
		SceneHierarchyPanel m_SceneHierarchyPanel;
		int32_t m_GizmoType = -1;
	};
}