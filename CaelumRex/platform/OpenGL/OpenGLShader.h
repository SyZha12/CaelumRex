#ifndef OPENGLSHADER_H
#define OPENGLSHADER_H

#include <cstdint>
#include <string>
#include <glm/glm.hpp>
#include <glad/glad.h>

#include "Renderer/Shader.h"

namespace CaelumRex
{
    class OpenGLShader : public Shader
    {
    public:
        OpenGLShader(const std::string& path);
        OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc);
        ~OpenGLShader() override;

        void Bind() const override;
        void Unbind() const override;

        void SetUniformInt(const std::string& name, int value);

        void SetUniformFloat(const std::string& name, float value);
        void SetUniformFloat2(const std::string& name, const glm::vec2& value);
        void SetUniformFloat3(const std::string& name, const glm::vec3& value);
        void SetUniformFloat4(const std::string& name, const glm::vec4& value);

        void SetUniformMat3(const std::string& name, const glm::mat3& matrix);
        void SetUniformMat4(const std::string& name, const glm::mat4& matrix);
    private:
        std::string ReadFile(const std::string& path);
        std::unordered_map<GLenum, std::string> PreProcess(const std::string& source);
        void Compile(const std::unordered_map<GLenum, std::string>& shaderSources);

        uint32_t m_ProgramID;
    };
}

#endif //OPENGLSHADER_H
