#ifndef MENURENDERER_HPP
#define MENURENDERER_HPP

#include <Rendering/Abstract/Renderer.hpp>
#include <Rendering/GUI/Button.hpp>

class Renderer2D : public Renderer
{
public:
   
   Renderer2D(Shader const& shader, glm::mat4 view, glm::mat4 projection);
   
   void pushObject(Renderable& object, float weight = 0.f);
   void render() override;
   
private:
   
   std::map<float, std::vector<Renderable*>> m_objects;
};

#endif // MENURENDERER_HPP