#include "fjpch.h"
#include "OpenGLContext.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Fejioa
{

	OpenGLContext::OpenGLContext(GLFWwindow* window)
		: m_WindowHandle(window)
	{
		FJ_CORE_ASSERT(m_WindowHandle, "Window handle is null!");
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		FJ_CORE_ASSERT(status, "Failed to initialize Glad!");

		FJ_CORE_INFO("OpenGL Info: ");
		FJ_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
		FJ_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
		FJ_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}

}