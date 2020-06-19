#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <Rendering/RenderStates.hpp>

class Renderer : public RenderStates
{
public:
   
   Renderer(Shader const& shader, glm::mat4 view, glm::mat4 projection) : RenderStates(shader, view, projection) {}
   virtual ~Renderer() = default;
   
   virtual void render() = 0;
};

#endif // RENDERER_HPP