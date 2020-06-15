#ifndef RENDERER_HPP
#define RENDERER_HPP

class Renderer
{
public:
   
   Renderer() = default;
   
   virtual void render() = 0;
};

#endif // RENDERER_HPP