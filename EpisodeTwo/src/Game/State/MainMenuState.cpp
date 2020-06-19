#include <Game/State/MainMenuState.hpp>
#include <Game/State/CreditsState.hpp>
#include <Game/State/PhaseOneState.hpp>

MainMenuState::MainMenuState(NeptuneProject& game)
 : State(game)
{
   // Load Textures
   ResourcesManager::LoadTextureFile("assets/ui/cursor.png");
   ResourcesManager::LoadTextureFile("assets/ui/title.png");
   ResourcesManager::LoadTextureFile("assets/ui/menu_background.png");
   ResourcesManager::LoadTextureFile("assets/ui/button.png");
//   ResourcesManager::LoadTextureFile("assets/ui/selector.png");
   
   // Load Shaders
//   ResourcesManager::LoadShaderFile("basic", "assets/shaders/basic.vs", "assets/shaders/basic.fs");
   ResourcesManager::LoadShaderFile("sprite", "assets/shaders/sprite.vs", "assets/shaders/sprite.fs");
   ResourcesManager::LoadShaderFile("text", "assets/shaders/text.vs", "assets/shaders/text.fs");
   
   // Load Fonts
   ResourcesManager::LoadFontFile("assets/fonts/dogica.ttf", 22);
   
   glm::vec2 windowSize = m_game.getWindow().getSize();
   m_menuRenderer.reset(new Renderer2D(ResourcesManager::GetShader("sprite"), glm::mat4(1.f), glm::ortho(0.f, windowSize.x, 0.f, windowSize.y )));
   
   m_cursor.reset(new Sprite(ResourcesManager::GetTexture("assets/ui/cursor.png")));
   m_cursor->setOrigin({ 0.f, m_cursor->getSize().y });
   
   m_background.reset(new Sprite(ResourcesManager::GetTexture("assets/ui/menu_background.png")));
   m_background->setSize(windowSize);
   
   m_title.reset(new Sprite(ResourcesManager::GetTexture("assets/ui/title.png")));
   m_title->setPosition({ windowSize.x / 2, 3 * windowSize.y / 4 });
   m_title->setOrigin({ m_title->getLocalBounds().z / 2.f, m_title->getLocalBounds().w / 2.f });
   
   m_playButton.reset(new Button(ResourcesManager::GetTexture("assets/ui/button.png"), "Play",
                             ResourcesManager::GetFont("assets/fonts/dogica.ttf"), ResourcesManager::GetShader("text")));
   m_playButton->setPosition({ windowSize.x / 2, windowSize.y / 6 * 3 });
   
   m_creditsButton.reset(new Button(ResourcesManager::GetTexture("assets/ui/button.png"), "Credits",
                             ResourcesManager::GetFont("assets/fonts/dogica.ttf"), ResourcesManager::GetShader("text")));
   m_creditsButton->setPosition({ windowSize.x / 2, windowSize.y / 6 * 2 });
   
   m_quitButton.reset(new Button(ResourcesManager::GetTexture("assets/ui/button.png"), "Quit",
                             ResourcesManager::GetFont("assets/fonts/dogica.ttf"), ResourcesManager::GetShader("text")));
   m_quitButton->setPosition({ windowSize.x / 2, windowSize.y / 6 });
}

void MainMenuState::handleEvent(SDL_Event const& event)
{
   if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
   {
      glm::vec2 mousePos = { static_cast<float>(event.button.x), static_cast<float>(m_game.getWindow().getSize().y - event.button.y) };
      if (m_playButton->isClicked(mousePos))
      {
         m_game.pushState<PhaseOneState>();
         m_game.popState();
      }
      if (m_creditsButton->isClicked(mousePos))
      {
         m_game.pushState<CreditsState>();
         m_game.popState();
      }
      if (m_quitButton->isClicked(mousePos))
         m_game.stop();
   }
}

void MainMenuState::update(uint32_t dt)
{
   int mouseX, mouseY;
   SDL_GetMouseState(&mouseX, &mouseY);
   m_cursor->setPosition({ mouseX, m_game.getWindow().getSize().y - mouseY });
}

void MainMenuState::render(RenderMaster& master)
{
   m_menuRenderer->pushObject(*m_background);
   m_menuRenderer->pushObject(*m_title, 1.f);
   m_menuRenderer->pushObject(*m_playButton, 1.f);
   m_menuRenderer->pushObject(*m_creditsButton, 1.f);
   m_menuRenderer->pushObject(*m_quitButton, 1.f);
   m_menuRenderer->pushObject(*m_cursor, 10.f);
   master.pushRenderer(*m_menuRenderer);
}