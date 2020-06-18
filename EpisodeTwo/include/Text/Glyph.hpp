#ifndef GLYPH_HPP
#define GLYPH_HPP

#include <Rendering/Texture.hpp>

class Glyph
{
public:
   
   Glyph(glm::ivec2 size, glm::ivec2 bearing, unsigned int advance, uint8_t const* data);
   
   inline Texture const& getTexture() const { return m_texture; }
   inline glm::ivec2 getSize()        const { return m_size;    }
   inline glm::ivec2 getBearing()     const { return m_bearing; }
   inline unsigned int getAdvance()   const { return m_advance; }
   
private:
   
   Texture m_texture;
   glm::ivec2 m_size;
   glm::ivec2 m_bearing;
   unsigned int m_advance;
};

#endif // GLYPH_HPP