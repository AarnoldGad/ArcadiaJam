#include <Core/ResourcesManager.hpp>
#include <NeptuneProject.hpp>
#include <stb_image/stb_image.h>

std::map<std::filesystem::path, std::unique_ptr<std::fstream>> ResourcesManager::s_files;
std::map<std::string, std::unique_ptr<Shader>> ResourcesManager::s_shaders;
std::map<std::filesystem::path, std::unique_ptr<Texture>> ResourcesManager::s_textures;

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
   if (IsFileLoaded(filePath))
      return true;
   
   std::fstream* file = new std::fstream(filePath, mode);
   if (!file)
   {
      NeptuneProject::GetLogger().logError("Unable to open file : ", filePath);
      return false;
   }
   
   if (!exists(filePath))
      return false;
      
   s_files.emplace(relative(filePath), file);
   return true;
}

bool ResourcesManager::IsFileLoaded(std::filesystem::path const& filePath)
{
   auto it = s_files.find(relative(filePath));
   return it != s_files.end() && *(it->second);
}

std::fstream& ResourcesManager::GetFile(std::filesystem::path const& filePath)
{
   if (!IsFileLoaded(filePath) && !LoadFile(filePath))
      exit(-1);
      
   return *(s_files.find(relative(filePath))->second);
}

bool ResourcesManager::UnloadFile(std::filesystem::path const& file)
{
   return s_files.erase(relative(file));
}

bool ResourcesManager::LoadShaderFile(std::string const& name, std::string const& vertex, std::string const& fragment, std::string const& geometry)
{
   if (IsShaderLoaded(name))
      return true;
   
   Shader* shader = new Shader;
   s_shaders.emplace(name, shader);
   return shader->loadFromFile(vertex, fragment, geometry);
}

bool ResourcesManager::IsShaderLoaded(std::string const& name)
{
   return s_shaders.find(name) != s_shaders.end();
}

Shader& ResourcesManager::GetShader(std::string const& name)
{
   if (!IsShaderLoaded(name))
   {
      NeptuneProject::GetLogger().logError("Unable to retrieve shader ", name);
      exit(-1);
   }
   
   return *(s_shaders.find(name)->second);
}

bool ResourcesManager::UnloadShader(std::string const& name)
{
   return s_shaders.erase(name);
}

bool ResourcesManager::LoadTextureFile(std::filesystem::path const& file)
{
   if (IsTextureLoaded(file))
      return true;
      
   Texture* tex = new Texture;
   s_textures.emplace(relative(file), tex);
   return tex->loadFromFile(file);
}

bool ResourcesManager::IsTextureLoaded(std::filesystem::path const& file)
{
   return s_textures.find(relative(file)) != s_textures.end();
}

Texture& ResourcesManager::GetTexture(std::filesystem::path const& file)
{
   if (!IsTextureLoaded(file) && !LoadTextureFile(file))
      return *nullTexture;
   
   return *(s_textures.find(file)->second);
}

bool ResourcesManager::UnloadTexture(std::filesystem::path const& file)
{
   return s_textures.erase(relative(file));
}

void ResourcesManager::Clear()
{
   s_files.clear();
   s_shaders.clear();
   s_textures.clear();
   // TODO Fonts
}