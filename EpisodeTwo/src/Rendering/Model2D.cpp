#include <Rendering/Model2D.hpp>

Model2D::Model2D(unsigned int mode, size_t vertexCount, unsigned int usage)
 : Model(mode, vertexCount, usage), m_texture(nullptr), m_textureRect(0.f), m_globalColor(1.f), m_bounds(0.f), m_needUpdateBounds(true) {}

void Model2D::render(Shader& shader)
{
   shader.setMatrix4("Model", getTransformsAsMatrix());
   
   if (m_needUpdate)
   {
      update();
      m_vertexArray.update();
   }
   
   if (m_texture)
      m_texture->bind();
      
   m_vertexArray.draw();
   
   Texture::Bind(0);
}

void Model2D::update()
{
   m_needUpdate = false;
   
   updatePositions();
   updateColors();
   updateTextureCoordinates();
}

void Model2D::updateColors()
{
   for (size_t i = 0; i < getPointCount(); ++i)
      m_vertexArray[i].setColor(m_globalColor);
}

void Model2D::updateTextureCoordinates()
{
   if (m_texture)
   {
      glm::vec4 rect(m_textureRect.x / static_cast<float>(m_texture->getSize().x),
                     m_textureRect.y / static_cast<float>(m_texture->getSize().y),
                     m_textureRect.z / static_cast<float>(m_texture->getSize().x),
                     m_textureRect.w / static_cast<float>(m_texture->getSize().y));

      float width  = getLocalBounds().z;
      float height = getLocalBounds().w;

      glm::vec2 ratio(width  > 0 ? (rect.z - rect.x) / width  : 0,
                      height > 0 ? (rect.w - rect.y) / height : 0);

      for (size_t i = 0; i < getPointCount(); ++i)
         m_vertexArray[i].setTextureCoordinates({ m_vertexArray[i].getPosition().x * ratio.x + rect.x,
                                                  m_vertexArray[i].getPosition().y * ratio.y + rect.y });
   }
}

void Model2D::updateBounds()
{
   if (m_needUpdate)
      updatePositions();
   
   for (size_t i = 0; i < getPointCount(); ++i)
   {
      if (m_vertexArray[i].getPosition().x < m_bounds.x) m_bounds.x = m_vertexArray[i].getPosition().x;
      if (m_vertexArray[i].getPosition().y < m_bounds.y) m_bounds.y = m_vertexArray[i].getPosition().y;
      if (m_vertexArray[i].getPosition().x > m_bounds.z) m_bounds.z = m_vertexArray[i].getPosition().x;
      if (m_vertexArray[i].getPosition().y > m_bounds.w) m_bounds.w = m_vertexArray[i].getPosition().y;
   }
   
   m_bounds.z = glm::distance(m_bounds.x, m_bounds.z);
   m_bounds.w = glm::distance(m_bounds.y, m_bounds.w);
   
   m_needUpdateBounds = false;
}

void Model2D::setTexture(Texture& texture, bool resetRect)
{
   m_texture = &texture;
   if (resetRect)
      setTextureRect({ 0.f, 0.f, m_texture->getSize().x, m_texture->getSize().y });
      
   m_needUpdate = true;
}

void Model2D::setTextureRect(glm::vec4 rect)
{
   m_textureRect = rect;
   m_needUpdate = true;
}

void Model2D::setColor(glm::vec4 color)
{
   m_globalColor = color;
   m_needUpdate = true;
}

Texture& Model2D::getTexture() const
{
   if (m_texture)
      return *m_texture;
   else
   {
      NeptuneProject::GetLogger().logError("Nullptr Texture");
      exit(-1);
   }
}

glm::vec4 Model2D::getLocalBounds()
{
   if (m_needUpdateBounds)
      updateBounds();
      
   return m_bounds;
}

glm::vec4 Model2D::getGlobalBounds()
{
   glm::vec4 pos = { getLocalBounds().x, getLocalBounds().y, 0.f, 1.f };
   glm::vec4 size = { getLocalBounds().z, getLocalBounds().w, 0.f, 1.f };
   
   pos = getTransformsAsMatrix() * pos;
   size = glm::scale(glm::mat4(1.f), glm::vec3(getScale(), 1.f)) * size;
   
   return glm::vec4(pos.x, pos.y, size.x, size.y);
}