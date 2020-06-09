#include <Logger.hpp>

std::string const Logger::LogLevelName[] = { "INFO", "DEBUG", "WARNING", "ERROR" };

Logger::Logger(std::string const& label, std::string const& fileName)
 : m_label(label), m_shouldOutputFile(false)
{
   if (!fileName.empty())
   {
      m_shouldOutputFile = true;
      m_file.open(fileName);
      if (!m_file)
         std::cout << "Unable to open file :" << fileName << std::endl; // TODO Error handling
   }
}

Logger::~Logger()
{
   
}