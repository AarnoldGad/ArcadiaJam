#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <Window.hpp>
#include <Logger.hpp>

class Application
{
public:

   static void Init(uint32_t flags);
   
   Application();
   
   void run();
   void stop();

   inline static Logger& GetLogger()
   { 
      static Logger logger("Episode Two", "ajep2.log");
      return logger;
   }

private:
   
   bool m_running;
   Window m_mainWindow;
};

#endif // APPLICATION_HPP