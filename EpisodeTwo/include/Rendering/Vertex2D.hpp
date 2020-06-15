#ifndef SIMPLEVERTEX_HPP
#define SIMPLEVERTEX_HPP

#include <Rendering/Vertex.hpp>

class Vertex2D : public Vertex
{
public:
   
   explicit Vertex2D(glm::vec2 pos = glm::vec2(0.f), glm::vec4 color = glm::vec4(1.f), glm::vec2 textureCoordinates = glm::vec2(0.f));
   ~Vertex2D() override = default;
   
   size_t getLocationCount() const override;
   size_t getByteSize() const override;
   AttribInfo getAttribInfo(size_t location) const override;
   void const* getAttrib(size_t location) const override;
   
   void setPosition(glm::vec2 pos);
   void setColor(glm::vec4 color);
   void setTextureCoordinates(glm::vec2 coordinates);
   
   inline glm::vec2 getPosition()           const { return m_pos;                }
   inline glm::vec4 getColor()              const { return m_color;              }
   inline glm::vec2 getTextureCoordinates() const { return m_textureCoordinates; }
   
private:
   
   glm::vec2 m_pos;
   glm::vec4 m_color;
   glm::vec2 m_textureCoordinates;
};

#endif // SIMPLEVERTEX_HPP