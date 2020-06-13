#ifndef MAINMENUSTATE_HPP
#define MAINMENUSTATE_HPP

#include <State.hpp>

class MainMenuState : public State
{
public:
   
   explicit MainMenuState(Application& app);
   
   void handleEvent(SDL_Event const& event);
   void update(uint32_t dt);
   void render(RenderMaster& master);
   
private:
   
   
};

#endif // MAINMENUSTATE_HPP