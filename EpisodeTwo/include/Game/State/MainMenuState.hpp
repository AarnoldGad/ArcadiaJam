#ifndef MAINMENUSTATE_HPP
#define MAINMENUSTATE_HPP

#include <Core/State.hpp>
#include <Rendering/Common/Renderer2D.hpp>

class MainMenuState : public State
{
public:
   
   explicit MainMenuState(Game& game);
   virtual ~MainMenuState() = default;
   
   void handleEvent(SDL_Event const& event);
   void update(uint32_t dt);
   void render(RenderMaster& master);
   
private:
   
   std::unique_ptr<Renderer2D> m_menuRenderer;
   
   std::unique_ptr<Sprite> m_background;
   std::unique_ptr<Sprite> m_title;
   
   std::unique_ptr<Button> m_playButton;
   std::unique_ptr<Button> m_creditsButton;
   std::unique_ptr<Button> m_quitButton;
};

#endif // MAINMENUSTATE_HPP