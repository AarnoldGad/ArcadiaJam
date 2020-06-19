#include <Rendering/Common/Vertex2D.hpp>
#include <NeptuneProject.hpp>

Vertex2D::Vertex2D(glm::vec2 pos, glm::vec4 color, glm::vec2 textureCoordinates)
 : m_pos(pos), m_color(color), m_textureCoordinates(textureCoordinates) {}

size_t Vertex2D::getLocationCount() const
{
   return 3;
}

size_t Vertex2D::getByteSize() const
{
   return sizeof(float) * 8;
}

AttribInfo Vertex2D::getAttribInfo(size_t location) const
{
   AttribInfo info;
   
   switch (location)
   {
      case 0:
         info.byteSize = sizeof(glm::vec2);
         info.size = 2;
         info.dataType = GL_FLOAT;
         info.normalized = GL_FALSE;
         return info;
      case 1:
         info.byteSize = sizeof(glm::vec4);
         info.size = 4;
         info.dataType = GL_FLOAT;
         info.normalized = GL_FALSE;
         return info;
      case 2:
         info.byteSize = sizeof(glm::vec2);
         info.size = 2;
         info.dataType = GL_FLOAT;
         info.normalized = GL_FALSE;
         return info;
      default:
         NeptuneProject::GetLogger().logError("No attribute information at location ", location);
         return info;
   }
}

void const* Vertex2D::getAttrib(size_t location) const
{
   switch (location)
   {
      case 0:
         return glm::value_ptr(m_pos);
      case 1:
         return glm::value_ptr(m_color);
      case 2:
         return glm::value_ptr(m_textureCoordinates);
      default:
         NeptuneProject::GetLogger().logError("No attribute at location ", location);
         return nullptr;
   }
}

void Vertex2D::setPosition(glm::vec2 pos)
{
   m_pos = pos;
}

void Vertex2D::setColor(glm::vec4 color)
{
   m_color = color;
}

void Vertex2D::setTextureCoordinates(glm::vec2 coordinates)
{
   m_textureCoordinates = coordinates;
}