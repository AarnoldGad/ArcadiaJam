#ifndef WINDOW_HPP
#define WINDOW_HPP

class Window
{
public:
   Window(std::string const& title, glm::vec4 rect);
   ~Window();
   
   void clear(glm::vec4 color);
   void swapBuffers();
   
   inline SDL_Window* getWindowHandle() const { return m_window; }
   
private:   
   SDL_Window* m_window;
   SDL_GLContext m_context;
};

#endif // WINDOW_HPP