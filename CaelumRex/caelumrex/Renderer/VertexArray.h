#ifndef VERTEXARRAY_H
#define VERTEXARRAY_H

namespace CaelumRex
{
    class VertexArray
    {
    public:
        virtual ~VertexArray() {}

        virtual void Bind() = 0;
        virtual void Unbind() = 0;

        static VertexArray* Create();
    };
}

#endif //VERTEXARRAY_H
