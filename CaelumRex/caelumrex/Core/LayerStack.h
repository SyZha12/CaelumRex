#ifndef LAYERSTACK_H
#define LAYERSTACK_H

/**
 * @author Symen Zhang
 * @brief The LayerStack class is used in conjunction with the Layer class. Each new layer is stacked on the LayerStack
 *        and will be updated on events etc. for each layer that is on the LayerStack.
 */

/** CaelumRex libraries **/
#include <Core/Layer.h>

namespace CaelumRex
{
    class LayerStack
    {
    public:
        LayerStack() = default;
        ~LayerStack();

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* overlay);
        void PopLayer(Layer* layer);
        void PopOverlay(Layer* overlay);

        std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
        std::vector<Layer*>::iterator end() { return m_Layers.end(); }
    private:
        std::vector<Layer*> m_Layers;
        unsigned int m_LayerInsertIndex = 0;
    };
}

#endif //LAYERSTACK_H
