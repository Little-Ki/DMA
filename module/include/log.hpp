#pragma once
#include <string>
#include <sstream>
#include <iostream>
#include <chrono>
#include <iomanip>

class Log
{
public:
    Log() = delete;

    static void print(const std::string &format)
    {
        prefix();
        printf_s(format.c_str());
        subfix();
    }

    template <typename T>
    static void print(const std::string &format, T value)
    {
        prefix();
        printf_s(format.c_str(), value);
        subfix();
    }

    template <typename T, typename... Args>
    static void print(const std::string &format, T value, Args... args)
    {
        prefix();
        printf_s(format.c_str(), value, args...);
        subfix();
    }

private:
    static void prefix()
    {
        const auto current_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        std::tm time_info;
        std::ostringstream oss;

        localtime_s(&time_info, &current_time);
        oss << std::put_time(&time_info, "%H:%M:%S");

        printf("[DMA @ %s]", oss.str().c_str());
    }

    static void subfix()
    {
        printf_s("\n");
    }
};