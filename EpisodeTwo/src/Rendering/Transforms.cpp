#include <Rendering/Transforms.hpp>
#include <glm/gtc/type_ptr.hpp>

Transforms::Transforms(glm::vec2 pos, glm::vec2 origin, glm::vec2 scale, float rotation)
 : m_pos(pos), m_origin(origin), m_scale(scale), m_rotation(rotation), m_needUpdateTransforms(true) {}
 
glm::mat4 const& Transforms::getTransformsAsMatrix() const
{
   if (m_needUpdateTransforms)
   {
      m_transforms = glm::mat4(1.f);
      m_transforms = glm::scale(m_transforms, glm::vec3(m_scale, 1.f));
      m_transforms = glm::translate(m_transforms, glm::vec3(m_pos, 0.f));
      m_transforms = glm::rotate(m_transforms, m_rotation, {0.f, 0.f, 1.f});
      m_transforms = glm::translate(m_transforms, glm::vec3(-m_origin, 0.f));
      
      m_needUpdateTransforms = false;
   }
   
   return m_transforms;
}

float const* Transforms::getTransformsAsArray() const
{
   return glm::value_ptr(getTransformsAsMatrix());
}

void Transforms::setPosition(glm::vec2 pos)
{
   m_pos = pos;
   m_needUpdateTransforms = true;
}

void Transforms::setOrigin(glm::vec2 origin)
{
   m_origin = origin;
   m_needUpdateTransforms = true;
}

void Transforms::setScale(glm::vec2 scale)
{
   m_scale = scale;
   m_needUpdateTransforms = true;
}

void Transforms::setRotation(float angle)
{
   m_rotation = angle;
   m_needUpdateTransforms = true;
}

void Transforms::move(glm::vec2 offset)
{
   m_pos += offset;
   m_needUpdateTransforms = true;
}

void Transforms::scale(glm::vec2 factor)
{
   m_scale *= factor;
   m_needUpdateTransforms = true;
}

void Transforms::rotate(float angle)
{
   m_rotation += angle;
   m_needUpdateTransforms = true;
}

