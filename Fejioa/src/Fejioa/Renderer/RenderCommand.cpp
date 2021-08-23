#include "fjpch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Fejioa
{
	
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI();

}