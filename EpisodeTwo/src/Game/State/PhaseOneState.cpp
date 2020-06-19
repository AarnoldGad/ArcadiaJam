#include <Game/State/PhaseOneState.hpp>

PhaseOneState::PhaseOneState(Game& game)
 : State(game)
{
   // Init
   glm::vec2 windowSize = m_game.getApplication().getWindow().getSize();

}

void PhaseOneState::handleEvent(SDL_Event const& event)
{
   
}

void PhaseOneState::update(uint32_t dt)
{
   
}

void PhaseOneState::render(RenderMaster& master)
{
   
}