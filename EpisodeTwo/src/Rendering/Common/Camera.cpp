#include <Rendering/Common/Camera.hpp>

Camera::Camera(glm::vec2 pos, glm::vec4 viewport, float rotation)
 : Transforms(pos, {0.f, 0.f}, {1.f, 1.f}, rotation)
{
   setViewport(viewport);
}

glm::mat4 const& Camera::getTransformsAsMatrix() const
{
   if (m_needUpdateTransforms)
   {
      m_transforms = glm::mat4(1.f);
      m_transforms = glm::scale(m_transforms, glm::vec3(m_scale, 1.f));
      m_transforms = glm::translate(m_transforms, glm::vec3(-m_pos, 0.f));
      m_transforms = glm::rotate(m_transforms, m_rotation, {0.f, 0.f, 1.f});
      m_transforms = glm::translate(m_transforms, glm::vec3(m_origin, 0.f));
      
      m_needUpdateTransforms = false;
   }
   
   return m_transforms;
}

void Camera::setViewport(glm::vec4 viewport)
{
   m_viewport = viewport;
   
   if (m_viewport.x < 0.f) // X < 0
      m_viewport.x = 0.f;
   if (m_viewport.y < 0.f) // Y < 0
      m_viewport.y = 0.f;
   if (m_viewport.z < 0.f) // Width < 0
      m_viewport.z = 1.f;
   if (m_viewport.w < 0.f) // Height < 0
      m_viewport.w = 1.f;
}