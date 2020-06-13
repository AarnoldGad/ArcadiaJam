#include <NeptuneProject.hpp>
#include <glad/glad.h>

bool NeptuneProject::s_gladInitialized = false;

void NeptuneProject::Init(uint32_t flags)
{
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
   
   if (!gladLoadGLLoader((GLADloadproc) SDL_GL_GetProcAddress))
   {
      GetLogger().logError("Error loading OpenGL");
      exit(1); // TODO Error handling
   }
   else
      s_gladInitialized = true;
   
   GetLogger().logDebug(" * OpenGL ", glGetString(GL_VERSION));
   GetLogger().logDebug(" *        ", glGetString(GL_RENDERER));
   GetLogger().logDebug(" *        ", glGetString(GL_VENDOR));
   GetLogger().logDebug(" *        ", glGetString(GL_SHADING_LANGUAGE_VERSION));
   
   ResourcesManager::Init();
}

void NeptuneProject::Quit()
{
   SDL_Quit();
}

NeptuneProject::NeptuneProject()
 : m_running(false), m_mainWindow("Arcadia Jam Ep2", { SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600 }), m_shouldPop(0) {}

void NeptuneProject::gameLoop()
{
   SDL_Event event;
   uint32_t deltaTime, startTime = SDL_GetTicks();
   
   while (m_running)
   {
      deltaTime = SDL_GetTicks() - startTime;
      startTime = SDL_GetTicks();
      
      for (; m_shouldPop > 0; --m_shouldPop)
         m_states.pop();
         
      State& currentState = *m_states.front();
      
      while (SDL_PollEvent(&event))
      {
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
               currentState.handleEvent(event);
               break;
         }
      }
      
      currentState.update(deltaTime);
      
      m_mainWindow.clear({ 0.8f, 0.5f, 0.2f, 1.0f });
      
      currentState.render(m_renderMaster);
      m_renderMaster.finish();
      
      m_mainWindow.swapBuffers();
      
      deltaTime = SDL_GetTicks() - startTime;
      if (deltaTime < 1000 / 60)
         SDL_Delay(1000 / 60 - deltaTime);
   }
}

void NeptuneProject::popState()
{
   if (++m_shouldPop >= m_states.size())
      m_shouldPop = m_states.size() ? m_states.size() - 1 : 0;
}

void NeptuneProject::stop()
{
   m_running = false;
}