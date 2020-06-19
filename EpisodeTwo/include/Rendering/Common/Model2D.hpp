#ifndef MODEL2D_HPP
#define MODEL2D_HPP

#include <Rendering/Abstract/Model.hpp>
#include <Rendering/Common/Vertex2D.hpp>

class Model2D : public Model<Vertex2D>
{
public:
   
   Model2D(unsigned int mode, size_t vertexCount, unsigned int usage);
   virtual ~Model2D() = default;
   
   virtual void render(RenderStates const& states) override;
   
   void setTexture(Texture const& texture, bool resetRect = true);
   void setTextureRect(glm::vec4 rect);
   void setColor(glm::vec4 color);
   
   Texture const& getTexture() const;
   inline glm::vec4 getTextureRect() const { return m_textureRect; }
   inline glm::vec4 getColor() const { return m_globalColor; }
   
   glm::vec4 getLocalBounds();
   glm::vec4 getGlobalBounds();
   
protected:
   
   virtual void update() override;
   
   virtual void updatePositions() = 0;
   virtual void updateColors();
   virtual void updateTextureCoordinates();
   virtual void updateBounds();
   
   Texture const* m_texture;
   glm::vec4 m_textureRect;
   glm::vec4 m_globalColor;
   
   glm::vec4 m_bounds;
   bool m_needUpdateBounds;
};

#endif // MODEL2D_HPP