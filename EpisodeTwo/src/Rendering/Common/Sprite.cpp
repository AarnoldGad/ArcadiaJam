#include <Rendering/Common/Sprite.hpp>
#include <Application.hpp>

Sprite::Sprite(Texture const& texture)
 : Model2D(GL_TRIANGLE_STRIP, 4, GL_STATIC_DRAW), m_size(texture.getSize()), m_targetColor(1.f), m_replaceColor(1.f)
{
   setTexture(texture);
}

void Sprite::render(RenderStates const& states)
{
   states.getShader().setVector4("TargetColor", m_targetColor);
   states.getShader().setVector4("ReplaceColor", m_replaceColor);
   
   Model2D::render(states);
}

void Sprite::updatePositions()
{
   m_vertexArray[0].setPosition({ 0.f     , 0.f      });
   m_vertexArray[1].setPosition({ 0.f     , m_size.y });
   m_vertexArray[2].setPosition({ m_size.x, 0.f      });
   m_vertexArray[3].setPosition({ m_size.x, m_size.y });
}

void Sprite::setSize(glm::uvec2 size)
{
   m_size = size;
   m_needUpdate = true;
}

void Sprite::setColorMap(glm::vec4 targetColor, glm::vec4 replaceColor)
{
   m_targetColor = targetColor;
   m_replaceColor = replaceColor;
}