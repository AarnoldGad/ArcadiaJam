#ifndef FONT_HPP
#define FONT_HPP

#include <Text/Glyph.hpp>

class Font
{
public:
   
   Font();
   
   bool loadFromFile(std::string const& file, int size);
   // TODO Load from bitmap
   
   Glyph const& getGlyph(int index) const;
   inline int getSize() const { return m_size; }
   
private:
   
   std::string m_file;
   std::map<char, Glyph> m_glyphs;
   int m_size;
};


#endif // FONT_HPP