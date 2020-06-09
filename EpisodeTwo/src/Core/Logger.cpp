#include <Logger.hpp>

std::string const Logger::LogLevelName[] = { "INFO", "DEBUG", "WARNING", "ERROR" };

Logger::Logger(std::string const& label, std::string const& fileName)
 : m_label(label), m_fileName(fileName)
{
   if (!m_fileName.empty())
      ResourcesManager::LoadFile(m_fileName, std::ios_base::out);
}
