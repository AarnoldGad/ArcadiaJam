#ifndef TEXTURE_HPP
#define TEXTURE_HPP

class Texture
{
public:
   
   Texture();
   ~Texture();
   
   bool loadFromFile(std::string const& file);
   bool loadFromMemory(glm::uvec2 size, unsigned int format, uint8_t const* data);
   void generateMimaps();
   
   void setSWrap(int wrap);
   void setTWrap(int wrap);
   void setMinFilter(int filter);
   void setMagFilter(int filter);
   void setBorderColor(glm::vec4 color);
   
   inline int       getSWrap()       const { return m_sWrap;       }
   inline int       getTWrap()       const { return m_tWrap;       }
   inline int       getMinFilter()   const { return m_minFilter;   }
   inline int       getMagFilter()   const { return m_magFilter;   }
   inline glm::vec4 getBorderColor() const { return m_borderColor; }
   
   inline unsigned int getHandle() const { return m_id; }
   inline glm::uvec2 getSize() const { return m_size; }
   
   void bind() const;
   static void Bind(unsigned int id);
   
private:
   
   unsigned int m_id;
   glm::uvec2 m_size;
   
   int m_sWrap;
   int m_tWrap;
   int m_minFilter;
   int m_magFilter;
   glm::vec4 m_borderColor;
   
};

#endif // TEXTURE_HPP