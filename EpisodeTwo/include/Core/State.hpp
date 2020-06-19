#ifndef STATE_HPP
#define STATE_HPP

class Game;
class RenderMaster;

class State
{
public:
   
   explicit State(Game& game) : m_game(game) {}
   virtual ~State() = default;
   
   virtual void handleEvent(SDL_Event const& event) = 0;
   virtual void update(uint32_t dt) = 0;
   virtual void render(RenderMaster& master) = 0;
   
protected:
   
   Game& m_game;
};

#endif // STATE_HPP