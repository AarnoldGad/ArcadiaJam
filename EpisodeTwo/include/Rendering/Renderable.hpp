#ifndef RENDERABLE_HPP
#define RENDERABLE_HPP

#include <Rendering/RenderStates.hpp>

class Renderable
{
public: 
   Renderable() = default;
   
   virtual void render(RenderStates const& states) = 0;
};

#endif // RENDERABLE_HPP