#include <Text/Glyph.hpp>

Glyph::Glyph(glm::uvec2 size, glm::uvec2 bearing, unsigned int advance, uint8_t const* data)
 : m_size(size), m_bearing(bearing), m_advance(advance)
{
   m_texture.loadFromMemory(m_size, GL_RED, data);
   m_texture.setSWrap(GL_CLAMP_TO_EDGE);
   m_texture.setTWrap(GL_CLAMP_TO_EDGE);
   m_texture.setMinFilter(GL_NEAREST);
   m_texture.setMagFilter(GL_NEAREST);
   m_texture.generateMimaps();
}