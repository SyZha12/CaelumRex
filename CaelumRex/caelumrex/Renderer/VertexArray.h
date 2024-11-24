#ifndef VERTEXARRAY_H
#define VERTEXARRAY_H

#include <memory>

#include "Buffer.h"

namespace CaelumRex
{
    class VertexArray
    {
    public:
        virtual ~VertexArray() {}

        virtual void Bind() = 0;
        virtual void Unbind() = 0;

        virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) = 0;
        virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) = 0;

        virtual const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() = 0;
        virtual const std::shared_ptr<IndexBuffer>& GetIndexBuffer() = 0;

        static VertexArray* Create();
    };
}

#endif //VERTEXARRAY_H
