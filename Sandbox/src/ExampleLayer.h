#pragma once

#include <Feijoa.h>

#include "Platform/OpenGL/OpenGLShader.h"

#include <imgui/imgui.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class ExampleLayer : public Feijoa::Layer
{
public:
	ExampleLayer();

	virtual void OnUpdate(Feijoa::Timestep ts) override;
	virtual void OnImGuiRender() override;
	virtual void OnEvent(Feijoa::Event& e) override;

private:
	Feijoa::ShaderLibrary m_ShaderLibrary;
	Feijoa::Ref<Feijoa::Shader> m_Shader;
	Feijoa::Ref<Feijoa::VertexArray> m_VertexArray;

	Feijoa::OrthographicCameraController m_CameraController;

	Feijoa::Ref<Feijoa::Shader> m_FlatColorShader;
	Feijoa::Ref<Feijoa::VertexArray> m_SquareVA;

	Feijoa::Ref<Feijoa::Texture2D> m_Texture, m_FejioaLogoTexture;

	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
};