#ifndef SHADER_H
#define SHADER_H

#include <cstdint>
#include <string>
#include <glm/glm.hpp>

namespace CaelumRex
{
    class Shader
    {
    public:
        Shader(const std::string& vertexSrc, std::string& fragmentSrc);
        ~Shader();

        void Bind() const;
        void Unbind() const;

        void SetUniformMat4(const std::string& name, const glm::mat4& matrix);
    private:
        uint32_t m_ProgramID;
    };
}


#endif //SHADER_H
