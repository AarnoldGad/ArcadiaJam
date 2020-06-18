#ifndef SPRITE_HPP
#define SPRITE_HPP

#include <Rendering/Model2D.hpp>

class Sprite : public Model2D
{
public:
   
   Sprite();
   explicit Sprite(Texture& texture);
   
   void render(Shader& shader) override;
   
   void setSize(glm::uvec2 size);
   void setColorMap(glm::vec4 targetColor, glm::vec4 replaceColor);
   
   inline glm::uvec2 getSize() const { return m_size; }
   inline glm::vec4 getReplacementColor() const { return m_replaceColor; }
   inline glm::vec4 getTargetColor() const { return m_targetColor; }
   
private:

   void updatePositions() override;
   
   glm::uvec2 m_size;
   glm::vec4 m_targetColor;
   glm::vec4 m_replaceColor;
};

#endif // SPRITE_HPP