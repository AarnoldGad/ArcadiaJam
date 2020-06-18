#ifndef MAINMENUSTATE_HPP
#define MAINMENUSTATE_HPP

#include <State.hpp>
#include <Game/Rendering/Renderer2D.hpp>
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
   
   std::unique_ptr<Renderer2D> m_menuRenderer;
   
   Sprite* m_cursor;
   Sprite* m_background;
   Sprite* m_title;
   
   Button* m_playButton;
   Button* m_creditsButton;
   Button* m_quitButton;
   
   uint32_t m_buttonHoverTime;
};

#endif // MAINMENUSTATE_HPP