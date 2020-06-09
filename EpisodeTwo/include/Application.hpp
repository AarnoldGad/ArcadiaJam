#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <Window.hpp>
#include <Logger.hpp>

class Application
{
public:

   static void Init(uint32_t flags);
   
   Application();
   ~Application();
   
   void run();
   void stop();

   inline static Logger& GetMainLogger() { return s_mainLogger; }

private:
   
   bool m_running;
   Window m_mainWindow;
   static Logger s_mainLogger;
};

#endif // APPLICATION_HPP