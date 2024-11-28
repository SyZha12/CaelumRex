#ifndef TEXTURE_H
#define TEXTURE_H

/** CaelumRex libraries **/
#include <Core/Core.h>
/** Third-Party Libraries & Co **/
#include <cstdint>

namespace CaelumRex
{
    class Texture
    {
    public:
        virtual ~Texture() = default;

        virtual uint32_t GetWidth() const = 0;
        virtual uint32_t GetHeight() const = 0;

        virtual void Bind(uint32_t slot = 0) const = 0;
    };

    class Texture2D : public Texture
    {
    public:
        static Ref<Texture2D> Create(const std::string& path);
    };

}

#endif //TEXTURE_H