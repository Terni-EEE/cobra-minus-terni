#pragma once

#include <windows.h>

void LogToOutputWindow(const char* message)
{
    OutputDebugStringA(message);
}