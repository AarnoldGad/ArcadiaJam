#ifndef RESOURCESMANAGER_HPP
#define RESOURCESMANAGER_HPP

#include <filesystem>
#include <Rendering/Shader.hpp>
#include <Rendering/Texture.hpp>

class ResourcesManager
{
public:
   
   ResourcesManager() = delete;
   
   static void Init();
   
   static bool LoadFile(std::filesystem::path const& filePath, std::ios_base::openmode mode = std::ios_base::in | std::ios_base::out);
   static bool IsFileLoaded(std::filesystem::path const& filePath);
   static std::fstream& GetFile(std::filesystem::path const& filePath);
   static bool UnloadFile(std::filesystem::path const& file);
   
   static bool LoadShaderFile(std::string const& name, std::string const& vertex, std::string const& fragment, std::string const& geometry = std::string());
   static bool IsShaderLoaded(std::string const& name);
   static Shader& GetShader(std::string const& name);
   static bool UnloadShader(std::string const& name);
   
   static bool LoadTextureFile(std::filesystem::path const& file);
   static bool IsTextureLoaded(std::filesystem::path const& file);
   static Texture& GetTexture(std::filesystem::path const& file);
   static bool UnloadTexture(std::filesystem::path const& file);
   
   // TODO Load Font
   
   static void Clear();
   
private:
   
   static std::unique_ptr<Texture> nullTexture;
   
   static std::map<std::filesystem::path, std::unique_ptr<std::fstream>> s_files;
   static std::map<std::string, std::unique_ptr<Shader>> s_shaders;
   static std::map<std::filesystem::path, std::unique_ptr<Texture>> s_textures;
   // TODO fonts
   
};

#endif // RESOURCESMANAGER_HPP