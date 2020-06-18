#ifndef TEXT_HPP
#define TEXT_HPP

#include <Rendering/Model.hpp>
#include <Rendering/Vertex2D.hpp>

class Text : public Model<Vertex2D>
{
public:
   
   Text();
   Text(std::string const& text, Font const& font);
   virtual ~Text() = default;
   
   void render(RenderStates const& states) override;
   
   void setText(std::string const& text);
   void setFont(Font const& font);
   void setColor(glm::vec4 color);
   
   inline std::string getText()  const { return m_text;   }
   inline Font const& getFont()  const { return *m_font;  }
   inline glm::vec4   getColor() const { return m_color;  }
   
   glm::vec4 getLocalBounds();
   glm::vec4 getGlobalBounds();
   
private:

   void update() override;
   void updateBounds();
   
   std::string m_text;
   Font const* m_font;
   glm::vec4 m_color;
   glm::vec4 m_bounds;
   bool m_needUpdateBounds;
};

#endif // TEXT_HPP