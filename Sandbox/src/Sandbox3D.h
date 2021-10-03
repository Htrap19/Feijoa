#pragma once

#include <Feijoa.h>

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
	Feijoa::PerspectiveCameraController m_CameraController;

	Feijoa::Ref<Feijoa::Texture2D> m_CheckerboardTexture;
	Feijoa::Ref<Feijoa::Scene> m_ActiveScene;
	Feijoa::Entity m_Model;

	float m_FOV = 45.0f;
	glm::vec4 m_SquareColor = { 0.7f, 0.2f, 0.3f, 1.0f };
};
