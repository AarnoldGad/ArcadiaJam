#include <Application.hpp>
#include <Rendering/Text/Font.hpp>

Font::Font()
 : m_size(0) {}
 
bool Font::loadFromFile(std::string const& file, size_t size)
{
   glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
   
   m_glyphs.clear();
   m_file = file;
   m_size = size;
   FT_Face face;
   
   int error = FT_New_Face(Application::GetFreetype(), file.c_str(), 0, &face);
   if (error == FT_Err_Unknown_File_Format)
   {
      Application::GetLogger().logError("Unrecognized font format : ", m_file);
      return false;
   }
   else if (error)
   {
      Application::GetLogger().logError("Unable to load font : ", m_file);
      return false;
   }
   
   FT_Set_Pixel_Sizes(face, 0, m_size);
   FT_Select_Charmap(face, FT_ENCODING_UNICODE);
   
   Application::GetLogger().logDebug("Font ", file, " contains ", face->num_glyphs, " glyphs");
   
//   for (int index = 0; index < face->num_glyphs; ++index)
//   {
//      error = FT_Load_Char(face, index, FT_LOAD_RENDER);
//      if (error)
//      {
//         Application::GetLogger().logError("Unable to load glyph ", index, " from ", m_file);
//         continue;
//      }
//      
//      m_glyphs.emplace(index, Glyph({face->glyph->bitmap.width  , face->glyph->bitmap.rows},
//                                    {face->glyph->bitmap_left   , face->glyph->bitmap_top},
//                                     face->glyph->advance.x >> 6, face->glyph->bitmap.buffer));
//   }
//   
   unsigned int glyphIndex = 0;
   unsigned long charcode = 0;
   charcode = FT_Get_First_Char(face, &glyphIndex);
   while (glyphIndex != 0)
   {
      
      error = FT_Load_Char(face, charcode, FT_LOAD_RENDER);
      if (error)
      {
         Application::GetLogger().logError("Unable to load glyph ", charcode, " from ", m_file);
         continue;
      }
      
      m_glyphs.emplace(charcode, Glyph({face->glyph->bitmap.width  , face->glyph->bitmap.rows},
                                       {face->glyph->bitmap_left   , face->glyph->bitmap_top},
                                        face->glyph->advance.x >> 6, face->glyph->bitmap.buffer));
      
      charcode = FT_Get_Next_Char(face, charcode, &glyphIndex);
   }
   
   Application::GetLogger().logDebug("Font ", m_file, " loaded ", getGlyphCount(), " glyphs");
   FT_Done_Face(face);
   
   glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
   
   return true;
}

Glyph const& Font::getGlyph(unsigned long index) const
{
   try
   {
      return m_glyphs.at(index);
   }
   catch (std::out_of_range& e)
   {
      Application::GetLogger().logError("No glyph at index ", index, " from ", m_file);
      return m_glyphs.begin()->second;
   }
}