#ifndef SHADER_H
#define SHADER_H

#include <cstdint>
#include <string>

namespace CaelumRex
{
    class Shader
    {
    public:
        Shader(const std::string& vertexSrc, std::string& fragmentSrc);
        ~Shader();

        void Bind() const;
        void Unbind() const;
    private:
        uint32_t m_ProgramID;
    };
}


#endif //SHADER_H
