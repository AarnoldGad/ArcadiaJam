#ifndef RESOURCESMANAGER_HPP
#define RESOURCESMANAGER_HPP

#include <filesystem>

class ResourcesManager
{
public:
   
   ResourcesManager() = delete;
   
   static bool LoadFile(std::filesystem::path filePath, std::ios_base::openmode mode = std::ios_base::in | std::ios_base::out);
   static bool IsFileLoaded(std::filesystem::path filePath);
   static std::fstream& GetFile(std::filesystem::path filePath);
   
   // TODO Load Shader
   // TODO Load Texture
   // TODO Load Font
   
private:
   
   static std::map<std::filesystem::path, std::unique_ptr<std::fstream>> s_files;
   // TODO shaders
   // TODO textures
   // TODO fonts
   
};

#endif // RESOURCESMANAGER_HPP