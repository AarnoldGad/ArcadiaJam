#ifndef STATE_HPP
#define STATE_HPP

class Application;
class RenderMaster;

class State
{
public:
   
   explicit State(Application& app) : m_app(app) {}
   virtual ~State() = default;
   
   virtual void handleEvent(SDL_Event const& event) = 0;
   virtual void update(uint32_t dt) = 0;
   virtual void render(RenderMaster& master) = 0;
   
protected:
   
   Application& m_app;
};

#endif // STATE_HPP