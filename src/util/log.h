#pragma once
#include <string>
#include <memory>
#include "spdlog/common.h"
#include "spdlog/sinks/ansicolor_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_sinks.h"
#include "spdlog/sinks/base_sink.h"
#include "spdlog/details/os.h"

#define DEBUG_ENABLED
#ifdef DEBUG_ENABLED

#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

#define LOG_INFO(...) SPDLOG_LOGGER_CALL(Log::GetCoreLogger(), spdlog::level::info, __VA_ARGS__)
#define LOG_WARN(...) SPDLOG_LOGGER_CALL(Log::GetCoreLogger(), spdlog::level::warn, __VA_ARGS__)
#define LOG_DEBUG(...) SPDLOG_LOGGER_CALL(Log::GetCoreLogger(), spdlog::level::debug, __VA_ARGS__)
#define LOG_ERROR(...) SPDLOG_LOGGER_CALL(Log::GetCoreLogger(), spdlog::level::err, __VA_ARGS__)
#define LOG_CRITICAL(...) SPDLOG_LOGGER_CALL(Log::GetCoreLogger(), spdlog::level::critical, __VA_ARGS__)

#else 

#define LOG_INFO(...) (void)0
#define LOG_WARN(...) (void)0
#define LOG_DEBUG(...) (void)0
#define LOG_ERROR(...) (void)0
#define LOG_CRITICAL(...) (void)0

#endif

class Log {
public:
    static Log& Get() {
        static Log log;
        return log;
    }

    //Initialize spdlog
    static void Init() {
        //https://github.com/gabime/spdlog
        //
        Get().s_CoreLogger = spdlog::stdout_color_mt("Console"); //stdout_logger_mt("Console");
        Get().s_CoreLogger->set_level(spdlog::level::trace);
    
        LOG_INFO("INIT");
        LOG_INFO("Initialized logger");
        if (!spdlog::details::os::is_color_terminal()) {
            LOG_WARN("Terminal doesn't support colors {}", "false");
        }
        else {
            LOG_INFO("Terminal supports color");
        }
    }

    static std::shared_ptr<spdlog::logger>& GetCoreLogger() {
        return Get().s_CoreLogger;
    }

    std::shared_ptr<spdlog::logger>& GetCoreLoggerImpl() {
        return s_CoreLogger;
    }

private:
    std::shared_ptr<spdlog::logger> s_CoreLogger;
};

