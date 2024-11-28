#include "OpenGLShader.h"

#include <vector>
#include <fstream>

#include "Log.h"
#include "glm/gtc/type_ptr.hpp"

namespace CaelumRex
{

	static GLenum ShaderTypeFromString(const std::string& type)
	{
		if(type == "vertex")
			return GL_VERTEX_SHADER;
		if(type == "fragment")
			return GL_FRAGMENT_SHADER;

		CR_CORE_ERROR("Unknown shader type");
	}

	OpenGLShader::OpenGLShader(const std::string& path)
	{
		std::string source = ReadFile(path);
		auto shaderSources = PreProcess(source);
		Compile(shaderSources);

		auto lastSlash = path.find_last_of("/\\");
		lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;
		auto lastDot = path.rfind('.');
		auto count = lastDot == std::string::npos ? path.size() - lastSlash : lastDot - lastSlash;
		m_Name = path.substr(lastSlash, count);
	}

    OpenGLShader::OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
	    : m_Name(name)
    {
		std::unordered_map<GLenum, std::string> sources;
		sources[GL_VERTEX_SHADER] = vertexSrc;
		sources[GL_FRAGMENT_SHADER] = fragmentSrc;
		Compile(sources);
    }

    OpenGLShader::~OpenGLShader()
    {
		glDeleteProgram(m_ProgramID);
    }

    void OpenGLShader::Bind() const
    {
		glUseProgram(m_ProgramID);
    }

    void OpenGLShader::Unbind() const
    {
		glUseProgram(0);
    }

    void OpenGLShader::SetUniformInt(const std::string& name, int value)
    {
    	GLint location = glGetUniformLocation(m_ProgramID, name.c_str());
    	glUniform1i(location, value);
    }

    void OpenGLShader::SetUniformFloat(const std::string& name, float value)
    {
    	GLint location = glGetUniformLocation(m_ProgramID, name.c_str());
    	glUniform1f(location, value);
    }

    void OpenGLShader::SetUniformFloat2(const std::string& name, const glm::vec2& value)
    {
    	GLint location = glGetUniformLocation(m_ProgramID, name.c_str());
    	glUniform2f(location, value.x, value.y);
    }

    void OpenGLShader::SetUniformFloat3(const std::string& name, const glm::vec3& value)
    {
    	GLint location = glGetUniformLocation(m_ProgramID, name.c_str());
    	glUniform3f(location, value.x, value.y, value.z);
    }

    void OpenGLShader::SetUniformFloat4(const std::string& name, const glm::vec4& value)
    {
    	GLint location = glGetUniformLocation(m_ProgramID, name.c_str());
    	glUniform4f(location, value.x, value.y, value.z, value.w);
    }

    void OpenGLShader::SetUniformMat3(const std::string& name, const glm::mat3& matrix)
    {
    	GLint location = glGetUniformLocation(m_ProgramID, name.c_str());
    	glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
    }

    void OpenGLShader::SetUniformMat4(const std::string& name, const glm::mat4& matrix)
    {
		GLint location = glGetUniformLocation(m_ProgramID, name.c_str());
    	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
    }

    std::string OpenGLShader::ReadFile(const std::string& path)
    {
		std::string result;
		std::fstream in(path, std::ios::in | std::ios::binary);
		if(in)
		{
			in.seekg(0, std::ios::end);
			result.resize(in.tellg());
			in.seekg(0, std::ios::beg);
			in.read(&result[0], result.size());
			in.close();
		}
		else
		{
			CR_CORE_ERROR("Could not open file '{0}'", path);
		}

		return result;
    }

    std::unordered_map<GLenum, std::string> OpenGLShader::PreProcess(const std::string& source)
    {
		std::unordered_map<GLenum, std::string> shaderSources;

		const char* typeToken = "#type";
		size_t typeTokenLength = strlen(typeToken);
		size_t pos = source.find(typeToken, 0);
		while(pos != std::string::npos)
		{
			size_t eol = source.find_first_of("\r\n", pos);
			if(eol == std::string::npos)
				CR_CORE_ERROR("Shader PreProcess: Syntax error");
			size_t begin = pos + typeTokenLength + 1;
			std::string type = source.substr(begin, eol - begin);
			// if(type != "vertex" || type != "fragment")
			// 	CR_CORE_ERROR("Shader PreProcess: Invalid shader type specified");

			size_t nextLinePos = source.find_first_not_of("\r\n", eol);
			pos = source.find(typeToken, nextLinePos);
			shaderSources[ShaderTypeFromString(type)] = source.substr(nextLinePos, pos - (nextLinePos == std::string::npos ? source.size() - 1 : nextLinePos));
		}

		return shaderSources;
    }

    void OpenGLShader::Compile(const std::unordered_map<GLenum, std::string>& shaderSources)
    {
		GLuint program = glCreateProgram();
		std::array<GLenum, 2> glShaderIDs;
		int glShaderIDIndex = 0;
		for(auto& kv : shaderSources)
		{
			GLenum type = kv.first;
			const std::string& source = kv.second;

			// Create an empty vertex shader handle
			GLuint shader = glCreateShader(type);

			// Send the vertex shader source code to GL
			// Note that std::string's .c_str is NULL character terminated.
			const GLchar *sourceCStr = source.c_str();
			glShaderSource(shader, 1, &sourceCStr, 0);

			// Compile the vertex shader
			glCompileShader(shader);

			GLint isCompiled = 0;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
			if(isCompiled == GL_FALSE)
			{
				GLint maxLength = 0;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

				// The maxLength includes the NULL character
				std::vector<GLchar> infoLog(maxLength);
				glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

				// We don't need the shader anymore.
				glDeleteShader(shader);

				CR_CORE_ERROR("Shader type '{0}' compilation failed! {1}", type, infoLog.data());
				return;
			}

			glAttachShader(program, shader);
			glShaderIDs[glShaderIDIndex++] = shader;
		}

		// Vertex and fragment shaders are successfully compiled.
		// Now time to link them together into a program.
		// Get a program object.
		m_ProgramID = program;

		// Link our program
		glLinkProgram(program);

		// Note the different functions here: glGetProgram* instead of glGetShader*.
		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int *)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

			// We don't need the program anymore.
			glDeleteProgram(program);

			for(auto id : glShaderIDs)
				glDeleteShader(id);

			CR_CORE_ERROR("Shader linking failed! {0}", infoLog.data());
			return;
		}

		// Always detach shaders after a successful link.
		for(auto id : glShaderIDs)
			glDetachShader(program, id);
    }

}
