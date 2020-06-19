#include <Game/State/PhaseOneState.hpp>

PhaseOneState::PhaseOneState(NeptuneProject& game)
 : State(game)
{
   // Load
   ResourcesManager::LoadTextureFile("assets/ui/cursor.png");
   ResourcesManager::LoadTextureFile("assets/ui/dialog_box.png");
   ResourcesManager::LoadTextureFile("assets/ui/info_box.png");
   ResourcesManager::LoadTextureFile("assets/characters/jaeden.png");
   
   ResourcesManager::LoadShaderFile("sprite", "assets/shaders/sprite.vs", "assets/shaders/sprite.fs");
   ResourcesManager::LoadShaderFile("text", "assets/shaders/text.vs", "assets/shaders/text.fs");
//   ResourcesManager::LoadShaderFile("solar_system")
   
   ResourcesManager::LoadFontFile("assets/fonts/dogica.ttf", 12);
   
   // Init
   glm::vec2 windowSize = m_game.getWindow().getSize();
   
   m_cursorRenderer.reset(new Renderer2D(ResourcesManager::GetShader("sprite"), glm::mat4(1.f), glm::ortho(0.f, windowSize.x, 0.f, windowSize.y)));
   
   m_cursor.reset(new Sprite(ResourcesManager::GetTexture("assets/ui/cursor.png")));
   m_cursor->setOrigin({ 0.f, m_cursor->getSize().y });
}

void PhaseOneState::handleEvent(SDL_Event const& event)
{
   
}

void PhaseOneState::update(uint32_t dt)
{
   int mouseX, mouseY;
   SDL_GetMouseState(&mouseX, &mouseY);
   m_cursor->setPosition({ mouseX, m_game.getWindow().getSize().y - mouseY });
}

void PhaseOneState::render(RenderMaster& master)
{
   m_cursorRenderer->pushObject(*m_cursor);
   master.pushRenderer(*m_cursorRenderer, 10.f);
}