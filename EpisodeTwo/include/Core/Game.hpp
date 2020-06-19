#ifndef GAME_HPP
#define GAME_HPP

#include <Core/State.hpp>

class Application;

class Game
{
public:
   
   explicit Game(Application& app)
    : m_app(app), m_shouldPop(0) {}
   virtual ~Game() = default;
   
   virtual void handleEvent(SDL_Event const& event) = 0;
   virtual void update(uint32_t dt) = 0;
   virtual void render(RenderMaster& master) = 0;
   
   void updateState()
   {
      for (; m_shouldPop > 0; --m_shouldPop)
         m_states.pop();
   }
   
   template<typename S, typename... A>
   void pushState(A&&... args)
   {
      m_states.emplace(new S(*this, std::forward<A>(args)...));
   }
   
   void popState()
   {
      if (++m_shouldPop >= m_states.size())
         m_shouldPop = m_states.size() ? m_states.size() - 1 : 0;
   }
   
   inline Application& getApplication() const { return m_app; }
   
protected:
   
   Application& m_app;
   std::queue<std::unique_ptr<State>> m_states;
   unsigned int m_shouldPop;
};

#endif // GAME_HPP