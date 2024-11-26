#include "Shader.h"

#include "Renderer/Renderer.h"
#include "OpenGL/OpenGLShader.h"

namespace CaelumRex
{
	Shader* Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch(Renderer::getCurrentAPI())
		{
		case RendererAPI::API::None:
			CR_CORE_ERROR("Shader: RendererAPI::None is currently not supported."); return nullptr;
		case RendererAPI::API::OpenGL:
			return new OpenGLShader(vertexSrc, fragmentSrc);
		}

		CR_CORE_ERROR("Shader: Unknown RendererAPI.");
		return nullptr;
	}
}
