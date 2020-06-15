#ifndef NEPTUNEPROJECT_HPP
#define NEPTUNEPROJECT_HPP

#include <Rendering/Window.hpp>
#include <Rendering/RenderMaster.hpp>
#include <Core/Logger.hpp>
#include <State.hpp>

class NeptuneProject
{
public:

   static void Init(uint32_t flags);
   static void Quit();
   
   inline static FT_Library const GetFreetype() { return s_freetype; }
   
   static Logger& GetLogger();
   
   NeptuneProject();
   
   template<typename S, typename... A>
   void run(A&&... args);
   void stop();
   
   template<typename S, typename... A>
   void pushState(A&&... args);
   void popState();

private:
   
   void gameLoop();
   
   static Logger s_logger;
   static bool s_gladInitialized;
   static bool s_ftInitialized;
   static FT_Library s_freetype;
   
   bool m_running;
   Window m_mainWindow;
   RenderMaster m_renderMaster;
   std::queue<std::unique_ptr<State>> m_states;
   unsigned int m_shouldPop;
};

#include <NeptuneProject.inl>

#endif // NEPTUNEPROJECT_HPP