#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <ResourcesManager.hpp>

class Logger
{
public:

   enum LogLevel { INFO, DEBUG, WARNING, ERROR, LEVEL_COUNT };
   static std::string const LogLevelName[LEVEL_COUNT];

   explicit Logger(std::string const& label, std::string const& fileName = std::string());
   
   template<typename... A>
   void log(LogLevel level, A&&... msgs);
   
   template<typename... A>
   void logInfo(A&&... msgs);
   
   template<typename... A>
   void logDebug(A&&... msgs);
   
   template<typename... A>
   void logWarning(A&&... msgs);
   
   template<typename... A>
   void logError(A&&... msgs);
   
private:

   template<typename T>
   void log(std::ostream& output, T const& msg);
   template<typename T, typename... A>
   void log(std::ostream& output, T const& arg0, A&&... args);

   std::string m_label;
   std::string m_fileName; // TODO File opened in multiple loggers (Resources Manager)
   
};

#include <Logger.inl>

#endif // LOGGER_HPP