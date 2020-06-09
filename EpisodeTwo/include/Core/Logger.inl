template<typename T>
void Logger::log(std::ostream& output, T const& msg)
{
   output << msg;
}

template<typename T, typename... A>
void Logger::log(std::ostream& output, T const& arg0, A&&... args)
{
   log(output, arg0);
   log(output, std::forward<A>(args)...);
}

template<typename... A>
void Logger::log(LogLevel level, A&&... args)
{
   #if defined(_DEBUG)
   log(std::cout, "[", Logger::LogLevelName[level], "] [", m_label, "] ", std::forward<A>(args)...);
   log(std::cout, "\n");
   #else
   if (level == LogLevel::DEBUG)
      return;
   #endif
   
   if (!m_fileName.empty() && ResourcesManager::IsFileLoaded(m_fileName))
   {
      log(ResourcesManager::GetFile(m_fileName), "[", Logger::LogLevelName[level], "] [", m_label, "] ", std::forward<A>(args)...);
      log(ResourcesManager::GetFile(m_fileName), "\n");
   }
}

template<typename... A>
void Logger::logInfo(A&&... args)
{
   log(LogLevel::INFO, std::forward<A>(args)...);
}

template<typename... A>
void Logger::logDebug(A&&... args)
{
   log(LogLevel::DEBUG, std::forward<A>(args)...);
}

template<typename... A>
void Logger::logWarning(A&&... args)
{
   log(LogLevel::WARNING, std::forward<A>(args)...);
}

template<typename... A>
void Logger::logError(A&&... args)
{
   log(LogLevel::ERROR, std::forward<A>(args)...);
}
