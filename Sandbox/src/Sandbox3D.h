#pragma once

#include <Feijoa.h>
#include <glm/glm.hpp>

class Sandbox3D : public Feijoa::Layer
{
public:
	Sandbox3D();
	virtual ~Sandbox3D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	virtual void OnUpdate(Feijoa::Timestep ts) override;
	virtual void OnEvent(Feijoa::Event& e) override;

	virtual void OnImGuiRender() override;

private:
	bool OnWindowResize(Feijoa::WindowResizeEvent& e);

private:
	Feijoa::PerspectiveCameraController m_CameraController;

	Feijoa::Ref<Feijoa::Texture2D> m_CheckerboardTexture;
	Feijoa::Ref<Feijoa::Scene> m_ActiveScene;
	Feijoa::Entity m_Camera;
	Feijoa::Entity m_SphereModel;

	float m_FOV = 45.0f, m_Speed = 2.5f;
	glm::vec4 m_SquareColor = { 0.7f, 0.2f, 0.3f, 1.0f };
};
