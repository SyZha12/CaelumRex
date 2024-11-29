#ifndef LAYER_H
#define LAYER_H

/**
 *  @author Symen Zhang
 *  @brief Base class for layering; Base window is the default layer and each layer after can be stacked into the
 *         LayerStack.
 */

/** CaelumRex libraries **/
#include <Core/Timestep.h>
#include <Events/Event.h>

/** Third-Party Libraries & Co **/
#include <string>

namespace CaelumRex
{
    class Layer
    {
    public:
        explicit Layer(std::string_view name = "Layer");
        virtual ~Layer() = default;

        virtual void OnAttach() {}
        virtual void OnDetach() {}
        virtual void OnUpdate(Timestep ts) {}
        virtual void OnImGuiRender() {}
        virtual void OnEvent(Event& event) {}

        // Only for debug purposes
        [[nodiscard]] const std::string& GetName() const { return m_DebugName; }
    private:
        std::string m_DebugName;
    };
}

#endif //LAYER_H
