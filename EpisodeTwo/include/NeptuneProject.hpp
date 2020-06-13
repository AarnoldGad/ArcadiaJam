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
   
   NeptuneProject();
   
   template<typename S, typename... A>
   void run(A&&... args);
   void stop();
   
   template<typename S, typename... A>
   void pushState(A&&... args);
   void popState();

   inline static Logger& GetLogger()
   { 
      static Logger logger("Episode Two", "ajep2.log");
      return logger;
   }

private:
   
   void gameLoop();
   
   static bool s_gladInitialized;
   
   bool m_running;
   Window m_mainWindow;
   RenderMaster m_renderMaster;
   std::queue<std::unique_ptr<State>> m_states;
   unsigned int m_shouldPop;
};

#endif // NEPTUNEPROJECT_HPP