#include <Game/Rendering/RectangleModel.hpp>

RectangleModel::RectangleModel(glm::vec2 size, glm::vec4 color)
 : Model2D(GL_TRIANGLE_STRIP, 4, GL_STATIC_DRAW), m_size(size)
{
   setColor(color);
}

void RectangleModel::updatePositions()
{
   m_vertexArray[0].setPosition({ 0.f     , 0.f     });
   m_vertexArray[1].setPosition({ 0.f     , m_size.y});
   m_vertexArray[2].setPosition({ m_size.x, 0.f     });
   m_vertexArray[3].setPosition({ m_size.x, m_size.y});
}

void RectangleModel::setSize(glm::vec2 size)
{
   m_size = size;
   m_needUpdate = true;
}