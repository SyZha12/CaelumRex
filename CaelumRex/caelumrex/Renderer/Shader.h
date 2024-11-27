#ifndef SHADER_H
#define SHADER_H

#include <string>

namespace CaelumRex
{
    class Shader
    {
    public:
        virtual ~Shader() = default;

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        static Shader* Create(const std::string& path);
        static Shader* Create(const std::string& vertexSrc, const std::string& fragmentSrc);
    };
}


#endif //SHADER_H
