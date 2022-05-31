#pragma once
#include <windows.h>
#include <filesystem>
#include <cstdarg>
#include <fstream>
#include <iostream>
using namespace std;
namespace Core
{
    namespace Debug
    {
        class Log
        {
        public:
            ofstream logFile;
            static void DebugLog(const char* file, int line, const char* format, ...);
            void OpenFile(std::filesystem::path const& filename);
            void Print(const char* format, ...);
            ~Log();
        };
    }
}
