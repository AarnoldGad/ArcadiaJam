#include <Application.hpp>
#include <Core/ResourcesManager.hpp>
#include <Game/NeptuneProject.hpp>

int main(int argc, char* argv[])
{
   Application::Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
   Application app;
   
   app.run(new NeptuneProject(app));
   
   Application::Quit();
   
   // TODO 18th June
   // Refactor the whole mess -> Per Object Shader, UI classes, etc...
   // Phase One
   // Phase One Shader
   // Planet struct
   // Planet scenes
   // Phase Two
   // Scenes frames

   return 0;
}