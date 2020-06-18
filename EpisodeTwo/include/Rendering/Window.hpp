#ifndef WINDOW_HPP
#define WINDOW_HPP

class Window
{
public:
   Window(std::string const& title, glm::vec4 rect, uint32_t flags = 0);
   ~Window();
   
   void clear(glm::vec4 color);
   void swapBuffers();
   
   inline glm::vec2 getSize() const { return glm::vec2(m_rect.z, m_rect.w); }
   
   inline SDL_Window* getWindowHandle() const { return m_window; }
   
private:   
   SDL_Window* m_window;
   SDL_GLContext m_context;
   glm::vec4 m_rect;
};

#endif // WINDOW_HPP