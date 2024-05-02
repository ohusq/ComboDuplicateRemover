#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <fstream>
#include <Windows.h>
#include <ShlObj_core.h>

static bool isValidFileName(const std::string& fileName) {
    // Check if fileName contains illegal characters or path traversal components
    static const std::string illegalChars = "\\/:?\"<>|";
    if (fileName.find_first_of(illegalChars) != std::string::npos) {
        return false;
    }
    if (fileName.find("..") != std::string::npos) {
        return false;
    }
    return true;
}

int hasDuplicates(std::vector<std::wstring>& lines, const std::string& fileName) {
    if (!isValidFileName(fileName)) {
        std::cerr << "Invalid filename provided!\n";
        return -1; // Indicate an error
    }

    unsigned int counter = 0;
    std::unordered_set<std::wstring> seenLines;

    auto it = lines.begin();
    while (it != lines.end()) {
        if (seenLines.find(*it) != seenLines.end()) {
            it = lines.erase(it);
            ++counter;
        } else {
            seenLines.insert(*it);
            ++it;
        }
    }

    char saveLocation[MAX_PATH] = { 0 };
    SHGetSpecialFolderPathA(NULL, saveLocation, CSIDL_DESKTOPDIRECTORY, FALSE);

    std::string fullFilePath = std::string(saveLocation) + "\\" + fileName;
    std::ofstream newFile(fullFilePath);
    if (newFile.is_open()) {
        for (const auto& line : seenLines) {
            std::string narrowLine(line.begin(), line.end());
            newFile << narrowLine << "\n";
        }
        newFile.close();
    } else {
        std::cerr << "Failed to open file for writing!\n";
    }

    return counter; // Number of duplicates removed
}
