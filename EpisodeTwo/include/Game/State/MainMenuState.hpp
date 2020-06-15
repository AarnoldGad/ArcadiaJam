#ifndef MAINMENUSTATE_HPP
#define MAINMENUSTATE_HPP

#include <State.hpp>
#include <Game/Rendering/TestRenderer.hpp>

class MainMenuState : public State
{
public:
   
   explicit MainMenuState(NeptuneProject& game);
   
   void handleEvent(SDL_Event const& event);
   void update(uint32_t dt);
   void render(RenderMaster& master);
   
private:
   
   TestRenderer m_renderer;
};

#endif // MAINMENUSTATE_HPP