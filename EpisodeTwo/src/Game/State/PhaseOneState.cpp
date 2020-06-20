#include <Game/State/PhaseOneState.hpp>
#include <Game/State/MainMenuState.hpp>
#include <Game/Rendering/Palette.hpp>
#include <Rendering/Common/Colors.hpp>

PhaseOneState::PhaseOneState(Game& game)
 : State(game),
   m_planets{Planet("Galaxia", Colors::Cyan, 15.f, 90.f, 10.f),
             Planet("Galaxia", Colors::Red, 20.f, 160.f, 60.f),
             Planet("Galaxia", Colors::Green, 13.f, 220.f, 50.f),
             Planet("Galaxia", Colors::Blue, 10.f, 270.f, 30.f),
             Planet("Galaxia", Colors::Yellow, 25.f, 340.f, 25.f),
             Planet("Galaxia", Colors::Grey, 12.f, 430.f, 15.f),
             Planet("Galaxia", Colors::Red, 8.f, 500.f, 35.f),
             Planet("Galaxia", Colors::Green, 10.f, 600.f, 50.f),
             Planet("Galaxia", Palette::Blue, 8.f, 720.f, 15.f)}
{
   // Init
   glm::vec2 windowSize = m_game.getApplication().getWindow().getSize();

   m_spriteRenderer.reset(new Renderer2D(ResourcesManager::GetShader("sprite"), glm::mat4(1.f), glm::ortho(0.f, windowSize.x, 0.f, windowSize.y)));
   m_solarRenderer.reset(new Renderer2D(ResourcesManager::GetShader("solar"), glm::mat4(1.f), glm::ortho(0.f, windowSize.x, 0.f, windowSize.y)));

   m_backButton.reset(new Button(ResourcesManager::GetTexture("assets/ui/menu_button.png")));
   m_backButton->setPosition({ m_backButton->getSize().x / 2.f + 25.f, m_backButton->getSize().y / 2.f + 20.f });
   m_backButton->setScale({ 0.5f, 0.5f });
   
   m_infoBox.reset(new Sprite(ResourcesManager::GetTexture("assets/ui/info_box.png")));
   m_infoBox->setColorMap(Colors::Green, Palette::Violet);
   m_infoBox->setPosition({ windowSize.x - m_infoBox->getSize().x - 20.f, 20.f });
   
   m_solarBackground.reset(new RectangleModel(windowSize, { 0.05f, 0.f, 0.09f, 1.f }));
   
   Shader& solarShader = ResourcesManager::GetShader("solar");
   solarShader.bind();
   
   solarShader.setVector2("WindowSize", windowSize);
   
   for (size_t i = 0; i < 9; ++i)
   {
      solarShader.setVector4("PlanetsColor[" + std::to_string(i) + "]", m_planets[i].color);
      solarShader.setFloat("PlanetsRadius[" + std::to_string(i) + "]", m_planets[i].radius);
      solarShader.setFloat("PlanetsDistance[" + std::to_string(i) + "]", m_planets[i].orbitDistance);
      solarShader.setFloat("PlanetsAngle[" + std::to_string(i) + "]", m_planets[i].orbitAngle);
   }
   
   Shader::Bind(0);
}

void PhaseOneState::handleEvent(SDL_Event const& event)
{
   if (event.type == SDL_MOUSEBUTTONDOWN)
   {
      glm::vec2 mousePos = { static_cast<float>(event.button.x), static_cast<float>(m_game.getApplication().getWindow().getSize().y - event.button.y) };
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

void PhaseOneState::update(uint32_t dt)
{
   int mouseX, mouseY;
   SDL_GetMouseState(&mouseX, &mouseY);
   int hoveredPlanet = -1;
   for (size_t i = 0; i < 9; ++i)
   {
      float distance = glm::length(glm::vec4(m_planets[i].orbitDistance * glm::cos(glm::radians(m_planets[i].orbitAngle)) - mouseX,
                                             m_planets[i].orbitDistance * glm::sin(glm::radians(m_planets[i].orbitAngle)) - mouseY, 0.f, 1.f));
      if (distance <= m_planets[i].radius)
      {
         hoveredPlanet = i;
         break;
      }
   }
   Shader& solarShader = ResourcesManager::GetShader("solar");
   solarShader.bind();
   solarShader.setInteger("hoveredPlanet", hoveredPlanet);
   Shader::Bind(0);
}

void PhaseOneState::render(RenderMaster& master)
{
   m_solarRenderer->pushObject(*m_solarBackground);
   
   m_spriteRenderer->pushObject(*m_backButton);
   m_spriteRenderer->pushObject(*m_infoBox);
   
   master.pushRenderer(*m_solarRenderer, 0.f);
   master.pushRenderer(*m_spriteRenderer, 1.f);
}