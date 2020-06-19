#ifndef PHASEONESTATE_HPP
#define PHASEONESTATE_HPP

#include <Core/State.hpp>
#include <Rendering/Common/Renderer2D.hpp>

class PhaseOneState : public State
{
public:
   
   explicit PhaseOneState(NeptuneProject& game);
   virtual ~PhaseOneState() = default;
   
   void handleEvent(SDL_Event const& event);
   void update(uint32_t dt);
   void render(RenderMaster& master);
   
private:
   
   std::unique_ptr<Renderer2D> m_cursorRenderer;
   
   std::unique_ptr<Sprite> m_cursor;
};

#endif // PHASEONESTATE_HPP