#include <NeptuneProject.hpp>
#include <Core/ResourcesManager.hpp>
#include <Game/State/MainMenuState.hpp>

int main(int argc, char* argv[])
{
   NeptuneProject::Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
   NeptuneProject game;
   
   SDL_ShowCursor(SDL_DISABLE);
   
   game.run<MainMenuState>();
   
   SDL_ShowCursor(SDL_ENABLE);
   NeptuneProject::Quit();

   return 0;
}