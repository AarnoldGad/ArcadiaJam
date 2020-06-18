#include <Game/State/MainMenuState.hpp>

MainMenuState::MainMenuState(NeptuneProject& game)
 : State(game)
{
   // Load Textures
   ResourcesManager::LoadTextureFile("assets/ui/cursor.png");
   ResourcesManager::LoadTextureFile("assets/ui/title.png");
   ResourcesManager::LoadTextureFile("assets/ui/menu_background.png");
   ResourcesManager::LoadTextureFile("assets/ui/button.png");
   ResourcesManager::LoadTextureFile("assets/ui/selector.png");
   
   // Load Shaders
   ResourcesManager::LoadShaderFile("basic", "assets/shaders/basic.vs", "assets/shaders/basic.fs");
   ResourcesManager::LoadShaderFile("sprite", "assets/shaders/sprite.vs", "assets/shaders/sprite.fs");
   ResourcesManager::LoadShaderFile("text", "assets/shaders/text.vs", "assets/shaders/text.fs");
   
   // Load Fonts
   ResourcesManager::LoadFontFile("assets/fonts/pixel.ttf", 48);
   
   m_menuRenderer.reset(new MenuRenderer(m_game.getWindow()));
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
   master.pushRenderer(*m_menuRenderer);
}