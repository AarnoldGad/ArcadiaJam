#include <Rendering/OpenGL/Texture.hpp>
#include <Application.hpp>
#include <Core/Logger.hpp>

Texture::Texture()
 : m_id(0), m_size(0, 0), m_sWrap(GL_REPEAT), m_tWrap(GL_REPEAT),
   m_minFilter(GL_NEAREST), m_magFilter(GL_NEAREST), m_borderColor(0.f, 0.f, 0.f, 1.f)
{
   glGenTextures(1, &m_id);
}

bool Texture::loadFromFile(std::string const& file)
{
   int width, height, numChannel;
   uint8_t* data = stbi_load(file.c_str(), &width, &height, &numChannel, 0);
   if (!data)
   {
      Application::GetLogger().logError("Unable to load image at : ", file);
      return false;
   }
   else
   {
      loadFromMemory({ width, height }, (numChannel == 4 ? GL_RGBA : (numChannel == 3 ? GL_RGB : (numChannel == 2 ? GL_RG : GL_RED))), data);
      stbi_image_free(data);
      Application::GetLogger().logDebug("Texture ", file, " loaded");
      return true;
   }
}

// TODO GL error handling
bool Texture::loadFromMemory(glm::uvec2 size, unsigned int format, uint8_t const* data)
{
   bind();
   glTexImage2D(GL_TEXTURE_2D, 0, format, size.x, size.y, 0, format, GL_UNSIGNED_BYTE, data);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_sWrap);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_tWrap);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_minFilter);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_magFilter);
   glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, glm::value_ptr(m_borderColor));
   m_size = size;
   Bind(0);

   return true; // TODO
}

void Texture::generateMimaps()
{
   bind();
   glGenerateMipmap(GL_TEXTURE_2D);
   Bind(0);
}

void Texture::setSWrap(int wrap)
{
   m_sWrap = wrap;
   bind();
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_sWrap);
   Bind(0);
}

void Texture::setTWrap(int wrap)
{
   m_tWrap = wrap;
   bind();
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_tWrap);
   Bind(0);
}

void Texture::setMinFilter(int filter)
{
   m_minFilter = filter;
   bind();
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_minFilter);
   Bind(0);
}

void Texture::setMagFilter(int filter)
{
   m_magFilter = filter;
   bind();
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_magFilter);
   Bind(0);
}

void Texture::setBorderColor(glm::vec4 color)
{
   m_borderColor = color;
   bind();
   glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, glm::value_ptr(m_borderColor));
   Bind(0);
}

void Texture::bind() const
{
   Texture::Bind(m_id);
}

void Texture::Bind(unsigned int id)
{
   glBindTexture(GL_TEXTURE_2D, id);
}

Texture::~Texture()
{
//   glDeleteTextures(1, &m_id); // TODO Workaround lifetime problem when destructing temporary objects
}