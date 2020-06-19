#include <Application.hpp>
#include <Core/Logger.hpp>
#include <Core/State.hpp>

Logger Application::s_logger("Episode Two");
bool Application::s_gladInitialized = false;
bool Application::s_ftInitialized = false;
FT_Library Application::s_freetype = nullptr;

void Application::Init(uint32_t flags)
{
   s_logger.setOutputFile("ajep2.log");
   GetLogger().logDebug("Initialising Episode Two...");
   GetLogger().logDebug(" * Compiled for ", sizeof(size_t) * 8, "bit platform");
   
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
   else
      GetLogger().logDebug(" * SDL Initialized with flags ", flags);
   
   Window initWindow("Init", glm::vec4(0.f), SDL_WINDOW_HIDDEN);
   
   if (!s_gladInitialized && !gladLoadGLLoader((GLADloadproc) SDL_GL_GetProcAddress))
   {
      GetLogger().logError("Error loading OpenGL");
      exit(1); // TODO Error handling
   }
   
   if (!s_ftInitialized && FT_Init_FreeType(&s_freetype))
   {
      GetLogger().logError("Unable to load freetype");
      exit(-1);
   }
   
   s_gladInitialized = true;
   s_ftInitialized = true;
   
   GetLogger().logDebug(" * OpenGL ", glGetString(GL_VERSION));
   GetLogger().logDebug(" *        ", glGetString(GL_RENDERER));
   GetLogger().logDebug(" *        ", glGetString(GL_VENDOR));
   GetLogger().logDebug(" *        ", glGetString(GL_SHADING_LANGUAGE_VERSION));
   
   int major, minor, patch;
   FT_Library_Version(s_freetype, &major, &minor, &patch);
   GetLogger().logDebug(" * Freetype ", major, ".", minor, ".", patch);
   
   ResourcesManager::Init();
}

Logger& Application::GetLogger()
{ 
   return s_logger;
}

void Application::Quit()
{
   SDL_Quit();
   FT_Done_FreeType(s_freetype);
   ResourcesManager::Clear();
   s_ftInitialized = false;
}

Application::Application()
 : m_running(false), m_mainWindow("Arcadia Jam Ep2", { SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600 }) {}

void Application::run(Game* game)
{
   m_game.reset(game);
   m_running = true;
   GetLogger().logDebug("Running game...");
   gameLoop();
}

void Application::gameLoop()
{
   SDL_Event event;
   uint32_t deltaTime, startTime = SDL_GetTicks();
   
   while (m_running)
   {
      deltaTime = SDL_GetTicks() - startTime;
      startTime = SDL_GetTicks();
         
      m_game->updateState();
      
      while (SDL_PollEvent(&event))
      {
         switch (event.type)
         {
            case SDL_WINDOWEVENT:
               if (event.window.event == SDL_WINDOWEVENT_CLOSE)
                  stop();
               break;
            default:
               m_game->handleEvent(event);
               break;
         }
      }
      
      m_game->update(deltaTime);
      
      m_mainWindow.clear({ 0.8f, 0.5f, 0.2f, 1.0f });
      
      m_game->render(m_renderMaster);
      m_renderMaster.finish();
      
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