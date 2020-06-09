#include <Application.hpp>
#include <ResourcesManager.hpp>
#include <filesystem>

int main(int argc, char* argv[])
{
   Application::Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER);
   Application game;
   
   game.run();

   return 0;
}