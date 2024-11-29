/* CaelumRex Libraries */
#include <Renderer/Shader.h>
#include <Renderer/Renderer.h>
#include <OpenGL/OpenGLShader.h>

namespace CaelumRex
{
	Ref<Shader> Shader::Create(const std::string& path)
	{
		switch(Renderer::getCurrentAPI())
		{
		case RendererAPI::API::None:
			CR_CORE_ERROR("Shader: RendererAPI::None is currently not supported."); return nullptr;
		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLShader>(path);
		}

		CR_CORE_ERROR("Shader: Unknown RendererAPI.");
		return nullptr;
	}

	Ref<Shader> Shader::Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch(Renderer::getCurrentAPI())
		{
		case RendererAPI::API::None:
			CR_CORE_ERROR("Shader: RendererAPI::None is currently not supported."); return nullptr;
		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLShader>(name, vertexSrc, fragmentSrc);
		}

		CR_CORE_ERROR("Shader: Unknown RendererAPI.");
		return nullptr;
	}

	void ShaderLibrary::Add(const std::string& name, const Ref<Shader>& shader)
	{
		if(m_Shaders.find(name) != m_Shaders.end())
			CR_CORE_ERROR("Shader already exists");
		m_Shaders[name] = shader;
	}

	void ShaderLibrary::Add(const Ref<Shader>& shader)
	{
		auto& name = shader->GetName();
		Add(name, shader);
	}

	Ref<Shader> ShaderLibrary::Load(const std::string& path)
	{
		auto shader = Shader::Create(path);
		Add(shader);
		return shader;
	}

	Ref<Shader> ShaderLibrary::Load(const std::string& name, const std::string& path)
	{
		auto shader = Shader::Create(path);
		Add(shader);
		return shader;
	}

	Ref<Shader> ShaderLibrary::Get(const std::string& name)
	{
		if(m_Shaders.find(name) == m_Shaders.end())
			CR_CORE_ERROR("Shader not found");
		return m_Shaders[name];
	}
}
