#ifndef RENDERMASTER_HPP
#define RENDERMASTER_HPP

#include <Rendering/Abstract/Renderer.hpp>

class RenderMaster
{
public:
   
   RenderMaster() = default;
   
   void pushRenderer(Renderer& renderer, float weight = 0.f);
   
   void finish();
   
private:
   
   std::map<float, Renderer*> m_renderers;
};

#endif // RENDERMASTER_HPP