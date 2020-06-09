#include <Application.hpp>
#include <glad/glad.h>

void Application::Init(uint32_t flags)
{
   GetLogger().logDebug("Initialising Episode Two...");
   
   SDL_version sdlVersion;
   SDL_VERSION(&sdlVersion);
   GetLogger().logDebug(" * SDL compiled against ", +sdlVersion.major, ".", +sdlVersion.minor, ".", +sdlVersion.patch, " rev", SDL_GetRevisionNumber());
   SDL_GetVersion(&sdlVersion);
   GetLogger().logDebug(" * SDL linked against ", +sdlVersion.major, ".", +sdlVersion.minor, ".", +sdlVersion.patch, " rev", SDL_GetRevisionNumber());
   
   if (SDL_Init((SDL_WasInit(0) ^ flags) & flags))
   {
      GetLogger().logError("SDL Initialisation error : ", SDL_GetError());
      exit(1); // TODO Error handling
   }
}

Application::Application()
 : m_running(false), m_mainWindow("Arcadia Jam Ep2", { SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600 })
{
   if (!gladLoadGLLoader((GLADloadproc) SDL_GL_GetProcAddress))
   {
      GetLogger().logError("Error loading OpenGL");
      exit(1); // TODO Error handling
   }
   
   GetLogger().logDebug(" * OpenGL ", glGetString(GL_VERSION));
   GetLogger().logDebug(" *        ", glGetString(GL_RENDERER));
   GetLogger().logDebug(" *        ", glGetString(GL_VENDOR));
   GetLogger().logDebug(" *        ", glGetString(GL_SHADING_LANGUAGE_VERSION));
}

void Application::run()
{
   m_running = true;
   
   SDL_Event event;
   uint32_t deltaTime, startTime = SDL_GetTicks();
   
   while (m_running)
   {
      deltaTime = SDL_GetTicks() - startTime;
      startTime = SDL_GetTicks();
      
      SDL_PollEvent(&event);
      switch (event.type)
      {
         case SDL_WINDOWEVENT:
            if (event.window.event == SDL_WINDOWEVENT_CLOSE)
               stop();
            break;
         case SDL_KEYDOWN:
            stop();
            break;
         default:
            break;
      }
      
      m_mainWindow.clear({ 0.8f, 0.5f, 0.2f, 1.0f });
      
      // Rendering
      
      m_mainWindow.swapBuffers();
      
      deltaTime = SDL_GetTicks() - startTime;
      if (deltaTime < 1000 / 60)
         SDL_Delay(1000 / 60 - deltaTime);
   }
}

void Application::stop()
{
   m_running = false;
}