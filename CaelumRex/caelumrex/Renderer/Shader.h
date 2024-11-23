#ifndef SHADER_H
#define SHADER_H

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
        u_int32_t m_ProgramID;
    };
}


#endif //SHADER_H
