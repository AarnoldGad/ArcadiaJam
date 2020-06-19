#ifndef CREDITSSTATE_HPP
#define CREDITSSTATE_HPP

#include <Core/State.hpp>
#include <Rendering/Common/Renderer2D.hpp>

class CreditsState : public State
{
public:
   
   explicit CreditsState(Game& game);
   virtual ~CreditsState() = default;
   
   void handleEvent(SDL_Event const& event);
   void update(uint32_t dt);
   void render(RenderMaster& master);
   
private:
   
   std::unique_ptr<Renderer2D> m_mainRenderer;
   std::unique_ptr<Renderer2D> m_creditsRenderer;
   
   std::unique_ptr<Sprite> m_background;
   std::unique_ptr<Sprite> m_title;
   
   std::unique_ptr<Button> m_backButton;
   Text m_credits;
};

#endif // CREDITSSTATE_HPP