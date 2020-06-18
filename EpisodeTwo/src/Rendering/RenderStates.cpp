#include <Rendering/RenderStates.hpp>

RenderStates::RenderStates(Shader const& shader, glm::mat4 view, glm::mat4 projection)
 : m_shader(&shader), m_view(view), m_projection(projection) {}

void RenderStates::setShader(Shader const& shader)
{
   m_shader = &shader;
}

void RenderStates::setView(glm::mat4 view)
{
   m_view = view;
}

void RenderStates::setProjection(glm::mat4 projection)
{
   m_projection = projection;
}