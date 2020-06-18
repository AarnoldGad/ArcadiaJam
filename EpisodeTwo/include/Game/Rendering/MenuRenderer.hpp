#ifndef MENURENDERER_HPP
#define MENURENDERER_HPP

#include <Rendering/Renderer.hpp>
#include <Rendering/Window.hpp>
#include <Game/Rendering/MenuButton.hpp>

class MenuRenderer : public Renderer
{
public:
   
   MenuRenderer(Window const& window);
   virtual ~MenuRenderer();
   
   void render() override;
   void update(uint32_t dt);
   
private:
   
   glm::mat4 m_projection;
   
   Sprite* m_background;
   Sprite* m_title;
   
   
   Window const& m_window;
};

#endif // MENURENDERER_HPP