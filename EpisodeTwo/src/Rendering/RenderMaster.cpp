#include <Rendering/RenderMaster.hpp>

void RenderMaster::pushRenderer(Renderer& renderer, float weight)
{
   m_renderers.emplace(weight, &renderer);
}

void RenderMaster::finish()
{
   for (auto& it : m_renderers)
      it.second->render();
      
   m_renderers.clear();
}