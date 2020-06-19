#include <Game/State/CreditsState.hpp>
#include <Game/State/MainMenuState.hpp>

CreditsState::CreditsState(NeptuneProject& game)
 : State(game)
{
   // Load
   ResourcesManager::LoadTextureFile("assets/ui/cursor.png");
   ResourcesManager::LoadTextureFile("assets/ui/title.png");
   ResourcesManager::LoadTextureFile("assets/ui/menu_background.png");
   ResourcesManager::LoadTextureFile("assets/ui/button.png");
   ResourcesManager::LoadTextureFile("assets/ui/back_arrow.png");
   
   ResourcesManager::LoadShaderFile("sprite", "assets/shaders/sprite.vs", "assets/shaders/sprite.fs");
   ResourcesManager::LoadShaderFile("text", "assets/shaders/text.vs", "assets/shaders/text.fs");
   
   ResourcesManager::LoadFontFile("assets/fonts/dogica.ttf", 22);
   
   // Init
   glm::vec2 windowSize = m_game.getWindow().getSize();
   
   m_mainRenderer.reset(new Renderer2D(ResourcesManager::GetShader("sprite"), glm::mat4(1.f), glm::ortho(0.f, windowSize.x, 0.f, windowSize.y)));
   m_creditsRenderer.reset(new Renderer2D(ResourcesManager::GetShader("text"), glm::mat4(1.f), glm::ortho(0.f, windowSize.x, 0.f, windowSize.y)));
   m_cursorRenderer.reset(new Renderer2D(ResourcesManager::GetShader("sprite"), glm::mat4(1.f), glm::ortho(0.f, windowSize.x, 0.f, windowSize.y)));
   
   m_cursor.reset(new Sprite(ResourcesManager::GetTexture("assets/ui/cursor.png")));
   m_cursor->setOrigin({ 0.f, m_cursor->getSize().y });
   
   m_background.reset(new Sprite(ResourcesManager::GetTexture("assets/ui/menu_background.png")));
   m_background->setSize(windowSize);
   
   m_title.reset(new Sprite(ResourcesManager::GetTexture("assets/ui/title.png")));
   m_title->setPosition({ windowSize.x / 2, windowSize.y - 40.f});
   m_title->setOrigin({ m_title->getLocalBounds().z / 2.f, m_title->getLocalBounds().w });
   
   m_backButton.reset(new Button(ResourcesManager::GetTexture("assets/ui/back_arrow.png")));
   m_backButton->setPosition({ 30.f, 25.f });
   
   m_credits.setFont(ResourcesManager::GetFont("assets/fonts/dogica.ttf"));
   //A\nGame Designer\nKeromas\nA\nGraphics\nLucstanislash\nA\nSound Designed\nLecricreator\nA\nDevelopper\n- The Aarnold -
   m_credits.setText("DreamLoad Studio Team\n\n"
                     "Lead\n   KakarrotCake\n\n"
                     "Game Designer\n   Keromas\n\n"
                     "Graphics\n   Lucstanislash\n\n"
                     "Sound Designer\n   Lecricreator\n\n"
                     "Developper\n   The Aarnold");
   m_credits.setPosition({ windowSize.x / 2, windowSize.y / 2.3 });
   m_credits.setOrigin({ m_credits.getLocalBounds().z / 2, m_credits.getLocalBounds().w / 2 });
//   m_credits.setScale({ 0.9f, 0.9f });
}

void CreditsState::handleEvent(SDL_Event const& event)
{
   if (event.type == SDL_MOUSEBUTTONDOWN)
   {
      glm::vec2 mousePos = { static_cast<float>(event.button.x), static_cast<float>(m_game.getWindow().getSize().y - event.button.y) };
      if (m_backButton->isClicked(mousePos))
      {
         m_game.pushState<MainMenuState>();
         m_game.popState();
      }
   }
   else if (event.type == SDL_KEYDOWN)
   {
      if (event.key.keysym.sym == SDLK_ESCAPE)
      {
         m_game.pushState<MainMenuState>();
         m_game.popState();
      }
   }
}

void CreditsState::update(uint32_t dt)
{
   int mouseX, mouseY;
   SDL_GetMouseState(&mouseX, &mouseY);
   m_cursor->setPosition({ mouseX, m_game.getWindow().getSize().y - mouseY });
}

void CreditsState::render(RenderMaster& master)
{
   m_mainRenderer->pushObject(*m_background);
   m_mainRenderer->pushObject(*m_title, 1.f);
   m_mainRenderer->pushObject(*m_backButton, 1.f);
   
   m_creditsRenderer->pushObject(m_credits);
   
   m_cursorRenderer->pushObject(*m_cursor);
   
   master.pushRenderer(*m_mainRenderer, 0.f);
   master.pushRenderer(*m_creditsRenderer, 1.f);
   master.pushRenderer(*m_cursorRenderer, 2.f);
}