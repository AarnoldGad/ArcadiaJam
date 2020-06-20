#include <Game/NeptuneProject.hpp>
#include <Game/State/MainMenuState.hpp>
#include <Game/State/CreditsState.hpp>

NeptuneProject::NeptuneProject(Application& app)
 : Game(app)
{
   SDL_ShowCursor(SDL_DISABLE);
   
   ResourcesManager::LoadTextureFile("assets/ui/cursor.png");
   ResourcesManager::LoadTextureFile("assets/ui/title.png");
   ResourcesManager::LoadTextureFile("assets/ui/menu_background.png");
   ResourcesManager::LoadTextureFile("assets/ui/button.png");
   ResourcesManager::LoadTextureFile("assets/ui/menu_button.png");
   
   // Load Shaders
   ResourcesManager::LoadShaderFile("basic", "assets/shaders/basic.vs", "assets/shaders/basic.fs");
   ResourcesManager::LoadShaderFile("sprite", "assets/shaders/sprite.vs", "assets/shaders/sprite.fs");
   ResourcesManager::LoadShaderFile("text", "assets/shaders/text.vs", "assets/shaders/text.fs");
   ResourcesManager::LoadShaderFile("solar", "assets/shaders/basic.vs", "assets/shaders/solar.fs");
   
   // Load Fonts
   ResourcesManager::LoadFontFile("assets/fonts/dogica.ttf", 22);
   
   // Init
   glm::vec2 windowSize = m_app.getWindow().getSize();
   m_cursorRenderer.reset(new Renderer2D(ResourcesManager::GetShader("sprite"), glm::mat4(1.f), glm::ortho(0.f, windowSize.x, 0.f, windowSize.y)));
   
   m_cursor.reset(new Sprite(ResourcesManager::GetTexture("assets/ui/cursor.png")));
   m_cursor->setOrigin({ 0.f, m_cursor->getSize().y });
   
   pushState<MainMenuState>();
}

void NeptuneProject::handleEvent(SDL_Event const& event)
{
   m_states.front()->handleEvent(event);
}

void NeptuneProject::update(uint32_t dt)
{
   int mouseX, mouseY;
   SDL_GetMouseState(&mouseX, &mouseY);
   m_cursor->setPosition({ mouseX, m_app.getWindow().getSize().y - mouseY });
   
   m_states.front()->update(dt);
}

void NeptuneProject::render(RenderMaster& master)
{
   m_states.front()->render(master);
   
   m_cursorRenderer->pushObject(*m_cursor);
   master.pushRenderer(*m_cursorRenderer, 100.f);
}

NeptuneProject::~NeptuneProject()
{
   SDL_ShowCursor(SDL_ENABLE);
}