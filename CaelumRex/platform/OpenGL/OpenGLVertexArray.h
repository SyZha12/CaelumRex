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
        private:
            uint32_t m_RendererID;
    };
}

#endif //OPENGLVERTEXARRAY_H
