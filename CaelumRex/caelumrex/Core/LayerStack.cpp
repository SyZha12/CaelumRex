/* CaelumRex Libraries */
#include <Core/LayerStack.h>

namespace CaelumRex
{
    LayerStack::~LayerStack()
    {
        for(Layer* layer : m_Layers)
        {
            layer->OnDetach();
            delete layer;
        }
    }

    void LayerStack::PushLayer(Layer* layer)
    {
        m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex, layer);
        m_LayerInsertIndex++;
    }

    void LayerStack::PushOverlay(Layer* overlay)
    {
        m_Layers.emplace_back(overlay);
    }

    void LayerStack::PopLayer(Layer* layer)
    {
        if (const auto it = std::find(m_Layers.begin(), m_Layers.begin() + m_LayerInsertIndex, layer); it != m_Layers.begin() + m_LayerInsertIndex)
        {
            layer->OnDetach();
            m_Layers.erase(it);
            m_LayerInsertIndex--;
        }
    }

    void LayerStack::PopOverlay(Layer* overlay)
    {
        if (const auto it = std::find(m_Layers.begin() + m_LayerInsertIndex, m_Layers.end(), overlay); it != m_Layers.end())
        {
            overlay->OnDetach();
            m_Layers.erase(it);
        }
    }

}