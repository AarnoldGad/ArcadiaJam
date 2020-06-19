#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <Rendering/Window.hpp>
#include <Rendering/RenderMaster.hpp>
#include <Core/Logger.hpp>
#include <Core/Game.hpp>

class Application
{
public:

   static void Init(uint32_t flags);
   static void Quit();
   
   inline static FT_Library const GetFreetype() { return s_freetype; }
   
   static Logger& GetLogger();
   
   Application();
   
   void run(Game* game);
   void stop();

   inline Window& getWindow() { return m_mainWindow; }

private:
   
   void gameLoop();
   
   static Logger s_logger;
   static bool s_gladInitialized;
   static bool s_ftInitialized;
   static FT_Library s_freetype;
   
   bool m_running;
   Window m_mainWindow;
   RenderMaster m_renderMaster;
   std::unique_ptr<Game> m_game;
};

#endif // APPLICATION_HPP