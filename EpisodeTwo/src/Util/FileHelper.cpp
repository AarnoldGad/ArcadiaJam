#include <Util/FileHelper.hpp>
#include <NeptuneProject.hpp>

std::stringstream FileHelper::ToStream(std::string const& name)
{
   if (name.empty())
      return std::stringstream();
   
   std::ifstream file;
   file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
   try
   {
      file.open(name);
   }
   catch (std::ifstream::failure& e)
   {
      NeptuneProject::GetLogger().logError("Unable to read file at : ", name);
      return std::stringstream();
   }

   std::stringstream stream;
   stream << file.rdbuf();
   file.close();
   return stream;
}

std::string FileHelper::ToString(std::string const& name)
{
   return FileHelper::ToStream(name).str();
}