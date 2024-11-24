#ifndef OPENGLVERTEXARRAY_H
#define OPENGLVERTEXARRAY_H

#include <cstdint>

#include "Renderer/VertexArray.h"

namespace CaelumRex
{
    class OpenGLVertexArray : public VertexArray
    {
        public:
            OpenGLVertexArray();
            ~OpenGLVertexArray() override;

            void Bind() override;
            void Unbind() override;

            void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) override;
            void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) override;

            const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() override { return m_VertexBuffers; }
            const std::shared_ptr<IndexBuffer>& GetIndexBuffer() override { return m_IndexBuffer; }
        private:
            uint32_t m_RendererID;
            std::vector<std::shared_ptr<VertexBuffer>> m_VertexBuffers;
            std::shared_ptr<IndexBuffer> m_IndexBuffer;
    };
}

#endif //OPENGLVERTEXARRAY_H
