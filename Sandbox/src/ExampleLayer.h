#pragma once

#include <Fejioa.h>

#include "Platform/OpenGL/OpenGLShader.h"

#include <imgui/imgui.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class ExampleLayer : public Fejioa::Layer
{
public:
	ExampleLayer();

	virtual void OnUpdate(Fejioa::Timestep ts) override;
	virtual void OnImGuiRender() override;
	virtual void OnEvent(Fejioa::Event& e) override;

private:
	Fejioa::ShaderLibrary m_ShaderLibrary;
	Fejioa::Ref<Fejioa::Shader> m_Shader;
	Fejioa::Ref<Fejioa::VertexArray> m_VertexArray;

	Fejioa::OrthographicCameraController m_CameraController;

	Fejioa::Ref<Fejioa::Shader> m_FlatColorShader;
	Fejioa::Ref<Fejioa::VertexArray> m_SquareVA;

	Fejioa::Ref<Fejioa::Texture2D> m_Texture, m_FejioaLogoTexture;

	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
};