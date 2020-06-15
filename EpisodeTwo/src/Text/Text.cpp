#include <Text/Text.hpp>

Text::Text()
 : Model(GL_TRIANGLE_STRIP, 4, GL_STATIC_DRAW), m_font(nullptr), m_color(1.f), m_needUpdateBounds(true)
{
   m_vertexArray[0].setTextureCoordinates({ 0.f, 0.f });
   m_vertexArray[1].setTextureCoordinates({ 0.f, 1.f });
   m_vertexArray[2].setTextureCoordinates({ 1.f, 0.f });
   m_vertexArray[3].setTextureCoordinates({ 1.f, 1.f });
}

Text::Text(std::string const& text, Font const& font)
 : Model(GL_TRIANGLES, 4, GL_STATIC_DRAW), m_text(text), m_font(&font), m_color(1.f), m_needUpdateBounds(true)
{
   m_vertexArray[0].setTextureCoordinates({ 0.f, 0.f });
   m_vertexArray[1].setTextureCoordinates({ 0.f, 1.f });
   m_vertexArray[2].setTextureCoordinates({ 1.f, 0.f });
   m_vertexArray[3].setTextureCoordinates({ 1.f, 1.f });
}

void Text::render()
{
   if (m_needUpdate)
      update();
   
   float offset = 0, w, h;
   glm::vec2 penPos(0.f);
   
   for (char it : m_text)
   {
      Glyph glyph = m_font->getGlyph(it);
      penPos.x = offset + glyph.getBearing().x;
      penPos.y = glyph.getBearing().y - glyph.getSize().y;
      w = glyph.getSize().x;
      h = glyph.getSize().y;
      
      m_vertexArray[0].setPosition({ penPos.x, penPos.y + h });
      m_vertexArray[1].setPosition({ penPos.x, penPos.y });
      m_vertexArray[2].setPosition({ penPos.x + w, penPos.y + h});
      m_vertexArray[3].setPosition({ penPos.x + w, penPos.y });
      m_vertexArray.update();
      
      glyph.getTexture().bind();
      m_vertexArray.draw();
      Texture::Bind(0);
      
      offset += glyph.getAdvance();
   }
}

void Text::update()
{
   for (size_t i = 0; i < getPointCount(); ++i)
      m_vertexArray[i].setColor(m_color);
   
   m_needUpdate = false;
}

void Text::updateBounds()
{
   float width = 0, height = 0;
   
   for (char it : m_text)
   {
      glm::vec2 size = m_font->getGlyph(it).getSize();
      if (size.y > height)
         height = size.y;
      width += static_cast<float>(m_font->getGlyph(it).getAdvance());
   }
   
   m_bounds = {0.f, 0.f, width, height};
   
   m_needUpdateBounds = false;
}

void Text::setText(std::string const& text)
{
   m_text = text;
   m_needUpdateBounds = true;
}

void Text::setFont(Font const& font)
{
   m_font = &font;
   m_needUpdateBounds = true;
}

void Text::setColor(glm::vec4 color)
{
   m_color = color;
   m_needUpdate = true;
}

glm::vec4 Text::getLocalBounds()
{
   if (m_needUpdateBounds)
      updateBounds();
      
   return m_bounds;
}

glm::vec4 Text::getGlobalBounds()
{
   glm::vec2 pos = getTransformsAsMatrix() * glm::vec4(getLocalBounds().x, getLocalBounds().y, 0.f, 0.f);
   return glm::vec4(pos, getLocalBounds().z, getLocalBounds().w);
}

