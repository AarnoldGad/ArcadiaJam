#include <Game/State/MainMenuState.hpp>

MainMenuState::MainMenuState(NeptuneProject& game)
 : State(game)
{
   ResourcesManager::LoadTextureFile("assets/characters/ano.png");
   ResourcesManager::LoadShaderFile("text", "assets/shaders/text.vs", "assets/shaders/text.fs");
   ResourcesManager::LoadShaderFile("basic", "assets/shaders/basic.vs", "assets/shaders/basic.fs");
}

void MainMenuState::handleEvent(SDL_Event const& event)
{
   if (event.type == SDL_KEYDOWN)
      m_game.stop();
}

void MainMenuState::update(uint32_t dt)
{
   
}

void MainMenuState::render(RenderMaster& master)
{
   master.pushRenderer(m_renderer);
}