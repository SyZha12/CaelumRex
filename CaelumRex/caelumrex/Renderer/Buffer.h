#ifndef BUFFER_H
#define BUFFER_H

#include "glm/ext/vector_int3.hpp"

namespace CaelumRex
{
    class VertexBuffer
    {
    public:
        virtual ~VertexBuffer() {}

        virtual void Bind() = 0;
        virtual void Unbind() = 0;

        static VertexBuffer* Create(float* vertices, u_int32_t size);
    };

    class IndexBuffer
    {
    public:
        virtual ~IndexBuffer() {}

        virtual void Bind() = 0;
        virtual void Unbind() = 0;

        virtual u_int32_t GetCount() = 0;

        static IndexBuffer* Create(u_int32_t* indices, u_int32_t size);
    };
}

#endif //BUFFER_H
