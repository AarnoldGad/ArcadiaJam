#include <Game/State/MainMenuState.hpp>
#include <Game/State/CreditsState.hpp>
#include <Game/State/PhaseOneState.hpp>

MainMenuState::MainMenuState(Game& game)
 : State(game)
{
   glm::vec2 windowSize = m_game.getApplication().getWindow().getSize();
   m_menuRenderer.reset(new Renderer2D(ResourcesManager::GetShader("sprite"), glm::mat4(1.f), glm::ortho(0.f, windowSize.x, 0.f, windowSize.y )));
   
   m_background.reset(new Sprite(ResourcesManager::GetTexture("assets/ui/menu_background.png")));
   m_background->setSize(windowSize);
   
   m_title.reset(new Sprite(ResourcesManager::GetTexture("assets/ui/title.png")));
   m_title->setPosition({ windowSize.x / 2, 3 * windowSize.y / 4 });
   m_title->setOrigin({ m_title->getLocalBounds().z / 2.f, m_title->getLocalBounds().w / 2.f });
   
   m_playButton.reset(new Button(ResourcesManager::GetTexture("assets/ui/button.png"), "Play",
                             ResourcesManager::GetFont("assets/fonts/dogica.ttf", 22), ResourcesManager::GetShader("text")));
   m_playButton->setPosition({ windowSize.x / 2, windowSize.y / 6 * 3 });
   
   m_creditsButton.reset(new Button(ResourcesManager::GetTexture("assets/ui/button.png"), "Credits",
                             ResourcesManager::GetFont("assets/fonts/dogica.ttf", 22), ResourcesManager::GetShader("text")));
   m_creditsButton->setPosition({ windowSize.x / 2, windowSize.y / 6 * 2 });
   
   m_quitButton.reset(new Button(ResourcesManager::GetTexture("assets/ui/button.png"), "Quit",
                             ResourcesManager::GetFont("assets/fonts/dogica.ttf", 22), ResourcesManager::GetShader("text")));
   m_quitButton->setPosition({ windowSize.x / 2, windowSize.y / 6 });
}

void MainMenuState::handleEvent(SDL_Event const& event)
{
   if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
   {
      glm::vec2 mousePos = { static_cast<float>(event.button.x), static_cast<float>(m_game.getApplication().getWindow().getSize().y - event.button.y) };
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
         m_game.getApplication().stop();
   }
}

void MainMenuState::update(uint32_t dt)
{
   
}

void MainMenuState::render(RenderMaster& master)
{
   m_menuRenderer->pushObject(*m_background);
   m_menuRenderer->pushObject(*m_title, 1.f);
   m_menuRenderer->pushObject(*m_playButton, 1.f);
   m_menuRenderer->pushObject(*m_creditsButton, 1.f);
   m_menuRenderer->pushObject(*m_quitButton, 1.f);
   master.pushRenderer(*m_menuRenderer);
}