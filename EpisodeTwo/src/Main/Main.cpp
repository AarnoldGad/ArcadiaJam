#include <NeptuneProject.hpp>
#include <Core/ResourcesManager.hpp>
#include <Game/State/MainMenuState.hpp>
#include <Game/State/CreditsState.hpp>

int main(int argc, char* argv[])
{
   NeptuneProject::Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
   NeptuneProject game;
   
   SDL_ShowCursor(SDL_DISABLE);
   
   game.run<MainMenuState>();
   
   SDL_ShowCursor(SDL_ENABLE);
   NeptuneProject::Quit();
   
   // TODO 18th June
   // Refactor the whole mess
   // Phase One
   // Phase One Shader
   // Planet struct
   // Planet scenes
   // Phase Two
   // Scenes frames

   return 0;
}