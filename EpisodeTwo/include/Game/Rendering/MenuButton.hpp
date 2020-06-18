#ifndef MENUBUTTON_HPP
#define MENUBUTTON_HPP

#include <Rendering/Model2D.hpp>
#include <Text/Text.hpp>

class MenuButton : public Model2D
{
public:
   
   MenuButton();
   virtual ~MenuButton() = default;
   
   void setText(std::string const& text);
   
   inline std::string const& getText() const { return m_text.getText(); }
   
private:
   
   Text m_text;
};

#endif // MENUBUTTON_HPP