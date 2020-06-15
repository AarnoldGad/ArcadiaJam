#include <Core/Logger.hpp>

std::string const Logger::LogLevelName[] = { "INFO", "DEBUG", "WARNING", "ERROR" };

Logger::Logger(std::string const& label, std::string const& outFile)
 : m_label(label), m_outputFile(outFile)
{
   if (!m_outputFile.empty())
      ResourcesManager::LoadFile(m_outputFile, std::ios_base::out);
}

void Logger::setOutputFile(std::string const& file)
{
   m_outputFile = file;
   ResourcesManager::LoadFile(m_outputFile, std::ios_base::out);
}