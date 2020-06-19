#ifndef FONT_HPP
#define FONT_HPP

#include <Rendering/Text/Glyph.hpp>

class Font
{
public:
   
   Font();
   
   bool loadFromFile(std::string const& file, size_t size);
   // TODO Load from bitmap
   
   Glyph const& getGlyph(unsigned long index) const;
   inline size_t getGlyphCount() const { return m_glyphs.size(); }
   inline size_t getSize() const { return m_size; }
   
private:
   
   std::string m_file;
   std::map<unsigned long, Glyph> m_glyphs;
   size_t m_size;
};


#endif // FONT_HPP