#pragma once

#include <Feijoa.h>

class Sandbox2D : public Feijoa::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	virtual void OnUpdate(Feijoa::Timestep ts) override;
	virtual void OnImGuiRender() override;
	virtual void OnEvent(Feijoa::Event& e) override;

private:
	Feijoa::OrthographicCameraController m_CameraController;

	Feijoa::Ref<Feijoa::FrameBuffer> m_FrameBuffer;
	Feijoa::Ref<Feijoa::Texture2D> m_CheckerBoardTexture;

	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
};