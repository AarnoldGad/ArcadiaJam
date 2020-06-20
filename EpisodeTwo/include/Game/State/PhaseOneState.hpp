#ifndef PHASEONESTATE_HPP
#define PHASEONESTATE_HPP

#include <Core/State.hpp>
#include <Rendering/Common/Renderer2D.hpp>
#include <Rendering/GUI/Button.hpp>
#include <Game/Rendering/DialogBox.hpp>
#include <Game/Rendering/RectangleModel.hpp>

struct Planet
{
   Planet(std::string planetName, glm::vec4 planetColor, float planetRadius, float planetOrbitDistance, float planetOrbitAngle)
    : name(planetName), color(planetColor), radius(planetRadius), orbitDistance(planetOrbitDistance), orbitAngle(planetOrbitAngle) {}
   
   std::string name;
   glm::vec4 color;
   float radius;
   float orbitDistance;
   float orbitAngle;
};

class PhaseOneState : public State
{
public:
   
   explicit PhaseOneState(Game& game);
   virtual ~PhaseOneState() = default;
   
   void handleEvent(SDL_Event const& event);
   void update(uint32_t dt);
   void render(RenderMaster& master);
   
private:
   
   std::unique_ptr<Renderer2D> m_spriteRenderer;
   std::unique_ptr<Renderer2D> m_solarRenderer;
   
   std::unique_ptr<Button> m_backButton;
   std::unique_ptr<Sprite> m_infoBox;
   
   std::unique_ptr<RectangleModel> m_solarBackground;
   
   Planet const m_planets[9];
};

#endif // PHASEONESTATE_HPP