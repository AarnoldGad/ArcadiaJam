#ifndef CREDITSSTATE_HPP
#define CREDITSSTATE_HPP

#include <State.hpp>
#include <Text/Text.hpp>
#include <Rendering/Sprite.hpp>

class CreditsState : public State
{
public:
   
   explicit CreditsState(NeptuneProject& game);
   virtual ~CreditsState() = default;
   
   void handleEvent(SDL_Event const& event);
   void update(uint32_t dt);
   void render(RenderMaster& master);
   
private:
   
   std::unique_ptr<Button> m_backButton;
   std::unique_ptr<Sprite> m_title;
   
   Text m_credits;
};

#endif // CREDITSSTATE_HPP