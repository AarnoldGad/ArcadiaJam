#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <Rendering/Text/Text.hpp>
#include <Rendering/Common/Sprite.hpp>

// TODO Totally rework :)
class Button : public Sprite
{
public:
   
   explicit Button(glm::vec4 color);
   Button(glm::vec4 color, std::string const& text, Font const& font, Shader const& textShader);
   
   explicit Button(Texture const& texture);
   Button(Texture const& texture, std::string const& text, Font const& font, Shader const& textShader);

   virtual ~Button() = default;
   
   virtual void render(RenderStates const& states) override;
   
   bool isClicked(glm::vec2 point);
   
   void setText(std::string const& text);
   void setFont(Font const& font);
   void setTextShader(Shader const& shader);
   
   inline std::string getText() const { return m_text.getText(); }
   inline Font const& getFont() const { return m_text.getFont(); }
   inline Shader const& getTextShader() const { return *m_textShader; }
   
protected:
   
   Text m_text;
   Shader const* m_textShader;
};

#endif // BUTTON_HPP