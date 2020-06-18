#include <Core/ResourcesManager.hpp>
#include <NeptuneProject.hpp>
#include <Core/Logger.hpp>

std::map<std::filesystem::path, std::unique_ptr<std::fstream>> ResourcesManager::s_files;
std::map<std::string, std::unique_ptr<Shader>> ResourcesManager::s_shaders;
std::map<std::filesystem::path, std::unique_ptr<Texture>> ResourcesManager::s_textures;
std::map<std::filesystem::path, std::unique_ptr<Font>> ResourcesManager::s_fonts;

std::unique_ptr<Texture> ResourcesManager::nullTexture;

void ResourcesManager::Init()
{
   stbi_set_flip_vertically_on_load(true);
   
   nullTexture.reset(new Texture);
   uint8_t data[12] = { 255, 0, 0,
                        0, 255, 0,
                        0, 0, 255,
                        255, 255, 255 };
                        
   nullTexture->loadFromMemory({ 2, 2 }, GL_RGB, data);
}

bool ResourcesManager::LoadFile(std::filesystem::path const& filePath, std::ios_base::openmode mode)
{
   auto result = s_files.try_emplace(relative(filePath), std::make_unique<std::fstream>(filePath, mode));
   
   if (!*result.first->second)
   {
      NeptuneProject::GetLogger().logError("Unable to open file : ", filePath);
      return false;
   }
   
   return result.second ? exists(filePath) : true;
}

bool ResourcesManager::IsFileLoaded(std::filesystem::path const& filePath)
{
   auto it = s_files.find(relative(filePath));
   return it != s_files.end() && *(it->second);
}

std::fstream& ResourcesManager::GetFile(std::filesystem::path const& filePath)
{
   if (!IsFileLoaded(filePath) /*&& !LoadFile(filePath)*/)
      exit(-1);
      
   return *s_files.at(relative(filePath));
}

bool ResourcesManager::UnloadFile(std::filesystem::path const& file)
{
   return s_files.erase(relative(file));
}

bool ResourcesManager::LoadShaderFile(std::string const& name, std::string const& vertex, std::string const& fragment, std::string const& geometry)
{
   auto result = s_shaders.try_emplace(name, std::make_unique<Shader>());
   return result.second ? result.first->second->loadFromFile(vertex, fragment, geometry) : true;
}

bool ResourcesManager::IsShaderLoaded(std::string const& name)
{
   return s_shaders.find(name) != s_shaders.end();
}

Shader& ResourcesManager::GetShader(std::string const& name)
{
   try
   {
      return *s_shaders.at(name);
   }
   catch (std::out_of_range& e)
   {
      NeptuneProject::GetLogger().logError("Unable to retrieve shader ", name);
      exit(-1);
   }
}

bool ResourcesManager::UnloadShader(std::string const& name)
{
   return s_shaders.erase(name);
}

bool ResourcesManager::LoadTextureFile(std::filesystem::path const& file)
{
   auto result = s_textures.try_emplace(relative(file), std::make_unique<Texture>());
   return result.second ? result.first->second->loadFromFile(file) : true;
}

bool ResourcesManager::IsTextureLoaded(std::filesystem::path const& file)
{
   return s_textures.find(relative(file)) != s_textures.end();
}

Texture& ResourcesManager::GetTexture(std::filesystem::path const& file)
{
   if (!IsTextureLoaded(file) && !LoadTextureFile(file))
      return *nullTexture;
   
   return *s_textures.at(relative(file));
}

bool ResourcesManager::UnloadTexture(std::filesystem::path const& file)
{
   return s_textures.erase(relative(file));
}

bool ResourcesManager::LoadFontFile(std::filesystem::path const& file, int fontSize)
{
   auto result = s_fonts.emplace(relative(file), std::make_unique<Font>());
   return result.second ? result.first->second->loadFromFile(file, fontSize) : true;
}

bool ResourcesManager::IsFontLoaded(std::filesystem::path const& file)
{
   return s_fonts.find(relative(file)) != s_fonts.end();
}

Font& ResourcesManager::GetFont(std::filesystem::path const& file)
{
   if (!IsFontLoaded(file) /*&& !LoadFontFile(file, 16)*/)
   {
      NeptuneProject::GetLogger().logError("Unable to retrieve font ", file);
      exit(-1);
   }
   
   return *s_fonts.at(relative(file));
}

bool ResourcesManager::UnloadFont(std::filesystem::path const& file)
{
   return s_fonts.erase(relative(file));
}

void ResourcesManager::Clear()
{
   NeptuneProject::GetLogger().logDebug("Unloading");
   s_files.clear();
   s_shaders.clear();
   s_textures.clear();
   s_fonts.clear();
}