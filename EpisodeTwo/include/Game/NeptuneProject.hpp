#ifndef NEPTUNEPROJECT_HPP
#define NEPTUNEPROJECT_HPP

#include <Core/Game.hpp>
#include <Rendering/Common/Sprite.hpp>
#include <Rendering/Common/Renderer2D.hpp>

class NeptuneProject : public Game
{
public:
   
   explicit NeptuneProject(Application& app);
   virtual ~NeptuneProject();
   
   void handleEvent(SDL_Event const& event) override;
   void update(uint32_t dt) override;
   void render(RenderMaster& master) override;
   
private:
   
   std::unique_ptr<Renderer2D> m_cursorRenderer;
   
   std::unique_ptr<Sprite> m_cursor;
};

#endif // NEPTUNEPROJECT_HPP