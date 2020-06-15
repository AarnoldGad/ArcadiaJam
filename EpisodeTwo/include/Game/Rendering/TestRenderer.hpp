#ifndef TESTRENDERER_HPP
#define TESTRENDERER_HPP

#include <Rendering/Renderer.hpp>
#include <Text/Text.hpp>

class TestRenderer : public Renderer
{
public:
   
   TestRenderer();
   
   void render() override;
   
private:
   
   Text m_text;
   glm::mat4 m_projection;
   Font m_font;
};

#endif // TESTRENDERER_HPP