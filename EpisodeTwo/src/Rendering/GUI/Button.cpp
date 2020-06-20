#include <Rendering/GUI/Button.hpp>

Button::Button(glm::vec4 color)
 : m_textShader(nullptr)
{
   setColor(color);
   setOrigin({ getSize().x / 2, getSize().y / 2 });
}

Button::Button(glm::vec4 color, std::string const& text, Font const& font, Shader const& textShader)
 : m_text(text, font), m_textShader(&textShader)
{
   setColor(color);
   setOrigin({ getSize().x / 2, getSize().y / 2 });
   m_text.setOrigin({ m_text.getLocalBounds().z / 2, m_text.getLocalBounds().w / 2});
}

Button::Button(Texture const& texture)
 : Sprite(texture), m_textShader(nullptr)
{
   setOrigin({ getSize().x / 2, getSize().y / 2 });
}

Button::Button(Texture const& texture, std::string const& text, Font const& font, Shader const& textShader)
 : Sprite(texture), m_text(text, font), m_textShader(&textShader)
{
   setOrigin({ getSize().x / 2, getSize().y / 2 });
   m_text.setOrigin({ m_text.getLocalBounds().z / 2, m_text.getLocalBounds().w / 2});
}

void Button::render(RenderStates const& states)
{
   Sprite::render(states);
   
   if (m_textShader)
   {
      m_textShader->bind();
      m_textShader->setMatrix4("View", states.getView());
      m_textShader->setMatrix4("Projection", states.getProjection());
      
      m_text.setPosition(getPosition());
      m_text.setRotation(getRotation());
      m_text.setScale(getScale());
      
      m_text.render(RenderStates(*m_textShader, states.getView(), states.getProjection()));
      
      states.getShader().bind();
   }
}

bool Button::isClicked(glm::vec2 point)
{
   glm::vec4 aabb = { (getPosition() - getOrigin()) * getScale(), glm::vec2(getSize()) * getScale() };
   if (point.x > aabb.x && point.x < aabb.x + aabb.z
    && point.y > aabb.y && point.y < aabb.y + aabb.w)
          return true;
   
   return false;
}

void Button::setText(std::string const& text)
{
   m_text.setText(text);
   m_text.setOrigin({ m_text.getLocalBounds().z / 2, m_text.getLocalBounds().w / 2});
}

void Button::setFont(Font const& font)
{
   m_text.setFont(font);
}

void Button::setTextShader(Shader const& shader)
{
   m_textShader = &shader;
}