#ifndef MAINMENUSTATE_HPP
#define MAINMENUSTATE_HPP

#include <State.hpp>
#include <Game/Rendering/MenuRenderer.hpp>
#include <Game/Rendering/TestRenderer.hpp>

class MainMenuState : public State
{
public:
   
   explicit MainMenuState(NeptuneProject& game);
   virtual ~MainMenuState() = default;
   
   void handleEvent(SDL_Event const& event);
   void update(uint32_t dt);
   void render(RenderMaster& master);
   
private:
   
   std::unique_ptr<MenuRenderer> m_menuRenderer;
};

#endif // MAINMENUSTATE_HPP