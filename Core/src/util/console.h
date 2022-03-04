class Console {
public:
    enum class LogLevel { INFO, WARN, ERROR, CRITICAL };

    template <typename ...Args>
    static void Log(LogLevel logLevel, const char* format, Args&&... args);

    static void Info();
    static void Warn();
    static void Error();
    static void Critical();
};
