#ifndef LAYER_H
#define LAYER_H

#include <string>

#include "caelumrex_export.h"
#include "Events/Event.h"

namespace CaelumRex
{
    class CAELUMREX_EXPORT Layer
    {
    public:
        Layer(const std::string& name = "Layer");
        virtual ~Layer() = default;

        virtual void OnAttach() {}
        virtual void OnDetach() {}
        virtual void OnUpdate() {}
        virtual void OnImGuiRender() {}
        virtual void OnEvent(Event& event) {}

        // Only for debug purposes
        const std::string& GetName() const { return m_DebugName; }
    private:
        std::string m_DebugName;
    };
}

#endif //LAYER_H
