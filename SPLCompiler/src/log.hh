#include <fstream>
#include <string>

class Logger
{
    std::ofstream out;

public:
    Logger(std::string logPath) : out(std::ofstream(logPath))
    {
    }
    Logger &print(std::string text)
    {
        out << text;
        return *this;
    }
    Logger &print(const char *text)
    {
        out << text;
        return *this;
    }
    Logger &println(std::string text)
    {
        out << text << std::endl;
        return *this;
    }
    Logger &println(const char *text)
    {
        out << text << std::endl;
        return *this;
    }
    Logger &println()
    {
        out << std::endl;
        return *this;
    }
    ~Logger()
    {
        out.close();
    }
};

extern Logger LexLogger;