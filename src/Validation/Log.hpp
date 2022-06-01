﻿#pragma once

#include <Utils/Meta/Concepts.hpp>
#include <Utils/Misc/CurrentFunction.hpp>
#include <Utils/Misc/ForceInline.hpp>

#include <iostream>
#include <filesystem>
#include <cstdio>
#include <ctime>
#include <iostream>
#include <string>

#ifdef VALIDATION_LOG_TO_CONSOLE
  #define LOG_MSG_TOKEN "\u001b[32m[Log]  \u001b[0m"
  #define DEBUG_LOG_MSG_TOKEN "\u001b[33m[Debug]\u001b[0m"
  #define ERROR_LOG_MSG_TOKEN "\u001b[31m[Error]\u001b[0m"
#else
  #define LOG_MSG_TOKEN "[Log]  "
  #define DEBUG_LOG_MSG_TOKEN "[Debug]"
  #define ERROR_LOG_MSG_TOKEN "[Error]"
#endif

namespace Validation::Log
{

  FORCEINLINE void PrintFormattedLine(const char* name, const char* file, const char* func, int line)
  {
    auto time = clock() * 1000 / CLOCKS_PER_SEC;
    auto time_str = std::to_string(time);
    std::printf("%s - %s Source: \"%s\", line %d, in %s:\n%*c", time_str.c_str(), name,
      std::filesystem::relative(file, SOURCE_DIR).generic_string().c_str(),
      line, func, time_str.length() + 11, ' ');
  }

  FORCEINLINE void PrintFormattedLine(const char* name)
  {
    std::printf("%d - %s ", clock() * 1000 / CLOCKS_PER_SEC, name);
  }

  template<typename ... Args>
  FORCEINLINE void _Log(const char* format, const Args&... args)
  {
    PrintFormattedLine(LOG_MSG_TOKEN);
    std::printf(format, args...);
    std::cout << std::endl;
  };

  template<typename ... Args>
  FORCEINLINE void _LogDebugV(const char* file, int line, const char* func, const char* format, const Args&... args)
  {
    PrintFormattedLine(DEBUG_LOG_MSG_TOKEN, file, func, line);
    std::printf(format, args...);
    std::cout << std::endl;
  };

  template<typename ... Args>
  FORCEINLINE void _LogDebug(const char* format, const Args&... args)
  {
    PrintFormattedLine(DEBUG_LOG_MSG_TOKEN);
    std::printf(format, args...);
    std::cout << std::endl;
  };


  template<unsigned flags, typename ... Args>
  FORCEINLINE void _LogDebugVF(const char* file, int line, const char* func, const char* format, const Args&... args)
  {
    if constexpr (LOGGING_FLAGS & flags)
    {
      PrintFormattedLine(DEBUG_LOG_MSG_TOKEN, file, func, line);
      std::printf(format, args...);
      std::cout << std::endl;
    }
  };

  template<unsigned flags, typename ... Args>
  FORCEINLINE void _LogDebugF(const char* format, const Args&... args)
  {
    if constexpr (LOGGING_FLAGS & static_cast<unsigned>(flags))
    {
      PrintFormattedLine(DEBUG_LOG_MSG_TOKEN);
      std::printf(format, args...);
      std::cout << std::endl;
    }
  };

  template<typename ... Args>
  FORCEINLINE void _LogError(const char* format, const Args&... args)
  {
    PrintFormattedLine(ERROR_LOG_MSG_TOKEN);
    std::printf(format, args...);
    std::cout << std::endl;
  };

  template<typename ... Args>
  FORCEINLINE void _LogErrorV(const char* file, int line, const char* func, const char* format, const Args&... args)
  {
    PrintFormattedLine(ERROR_LOG_MSG_TOKEN, file, func, line);
    std::printf(format, args...);
    std::cout << std::endl;
  };



  void InitLoggers();
}


#if defined(NDEBUG) && !defined(DEBUG_LOG_IN_RELEASE)
  // Basic debug logger
  #define LogDebug(...) static_cast<void>(0)
  
  // Basic verbose debug logger 
  #define LogDebugV(...) static_cast<void>(0)
  
  // Flagged verbose debug logger
  #define LogDebugVF(...) static_cast<void>(0)

  // Flagged debug logger
  #define LogDebugF(...) static_cast<void>(0)
#else
  // Basic debug logger
  #define LogDebug(...) Validation::Log::_LogDebug(__VA_ARGS__)

  // Basic verbose debug logger 
  #define LogDebugF(FLAGS, ...) Validation::Log::_LogDebugF<FLAGS>(__VA_ARGS__)

  // Flagged verbose debug logger
  #define LogDebugV(...) Validation::Log::_LogDebugV(__FILE__, __LINE__, CURRENT_FUNCTION, __VA_ARGS__)
  
  // Flagged debug logger
  #define LogDebugVF(FLAGS, ...) Validation::Log::_LogDebugVF<FLAGS>(__FILE__, __LINE__, CURRENT_FUNCTION, __VA_ARGS__)
#endif

// Basic logger
#define Log(...) Validation::Log::_Log(__VA_ARGS__)

// Basic error logger
#define LogError(...) Validation::Log::_LogError(__VA_ARGS__)

// Basic verbose error logger
#define LogErrorV(...) Validation::Log::_LogErrorV(__FILE__, __LINE__, CURRENT_FUNCTION, __VA_ARGS__)

