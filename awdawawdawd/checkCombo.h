#pragma once
#include <iostream>
#include <fstream>
#include <string>

bool hasNewLine(const std::wstring& filePath) {
    std::wifstream file(filePath); // Open the file
    if (!file.is_open()) {
        std::wcerr << L"Error: Unable to open file." << std::endl;
        return false;
    }

    wchar_t ch;
    while (file.get(ch)) {
        if (ch == L'\n') {
            file.close(); // Close the file
            return true; // Newline found, return true
        }
        if (ch == L'\r') { // In case of Windows-style line endings (CR+LF), '\r' may appear before '\n'
            continue; // Just skip '\r' characters
        }
    }

    file.close(); // Close the file
    return false; // No newline found
}