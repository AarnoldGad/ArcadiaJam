#include <Rendering/Window.hpp>
#include <NeptuneProject.hpp>
#include <glad/glad.h>

Window::Window(std::string const& title, glm::vec4 rect, uint32_t flags)
 : m_window(nullptr), m_context(nullptr)
{
   SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
   SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
   SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
   SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
   SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
   SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 0);
   SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 0);
   SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
   SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);
   //SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
   SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
   SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
   SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
   
   #if defined(_DEBUG)
      SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);
   #endif
   
   m_window = SDL_CreateWindow(title.c_str(), rect.x, rect.y, rect.z, rect.w, SDL_WINDOW_OPENGL | flags);
   if (!m_window)
   {
      NeptuneProject::GetLogger().logError("Window creation error : ", SDL_GetError());
      exit(1); // TODO Error handling
   }   
      
   m_context = SDL_GL_CreateContext(m_window);
   if (!m_context)
   {
      NeptuneProject::GetLogger().logError("Context creation error : ", SDL_GetError());
      exit(1); // TODO Error handling
   }
}

void Window::clear(glm::vec4 color)
{
   SDL_GL_MakeCurrent(m_window, m_context);
   glClearColor(color.r, color.g, color.b, color.a);
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void Window::swapBuffers()
{
   SDL_GL_MakeCurrent(m_window, m_context);
   SDL_GL_SwapWindow(m_window);
}

Window::~Window()
{
   SDL_GL_DeleteContext(m_context);
   SDL_DestroyWindow(m_window);
}