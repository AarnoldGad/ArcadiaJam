#include <ResourcesManager.hpp>
#include <Application.hpp>

std::map<std::filesystem::path, std::unique_ptr<std::fstream>> ResourcesManager::s_files;

bool ResourcesManager::LoadFile(std::filesystem::path filePath, std::ios_base::openmode mode)
{
   if (IsFileLoaded(filePath))
      return true;
   
   std::fstream* file = new std::fstream(filePath, mode);
   if (!file)
   {
      Application::GetLogger().logError("Unable to open file : ", filePath);
      return false;
   }
   
   if (!exists(filePath))
      return false;
      
   s_files.emplace(relative(filePath), file);
   return true;
}

bool ResourcesManager::IsFileLoaded(std::filesystem::path filePath)
{
   auto it = s_files.find(relative(filePath));
   return it != s_files.end() && *(it->second);
}

std::fstream& ResourcesManager::GetFile(std::filesystem::path filePath)
{
   if (!IsFileLoaded(filePath) && !LoadFile(filePath))
      exit(-1);
      
   return *(s_files.find(relative(filePath))->second);
}