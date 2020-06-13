#ifndef FILEHELPER_HPP
#define FILEHELPER_HPP

class FileHelper
{
public:
   
   FileHelper() = delete;
   
   static std::stringstream ToStream(std::string const& name);
   static std::string ToString(std::string const& name);
};

#endif // FILEHELPER_HPP

