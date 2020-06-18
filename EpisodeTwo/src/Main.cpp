#include <NeptuneProject.hpp>
#include <Core/ResourcesManager.hpp>
#include <Game/State/MainMenuState.hpp>

int main(int argc, char* argv[])
{
   NeptuneProject::Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
   NeptuneProject game;
   
   game.run<MainMenuState>();

   // TODO 14th June
   // Menu State
   // Phase 1
   
   NeptuneProject::Quit();

   return 0;
}