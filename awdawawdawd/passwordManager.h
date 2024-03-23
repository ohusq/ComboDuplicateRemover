#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <fstream>
#include <Windows.h>
#include <ShlObj_core.h>

int hasDuplicates(std::vector<std::wstring>& lines, const std::string& fileName) {
    unsigned int counter = 0;

    std::unordered_set<std::wstring> seenLines;

    auto it = lines.begin();
    while (it != lines.end()) {
        if (seenLines.find(*it) != seenLines.end()) {
            // Remove the duplicate line
            it = lines.erase(it);
            ++counter;
        }
        else {
            // Not a duplicate, add to set
            seenLines.insert(*it);
            ++it;
        }
    }

    // Write to the new file
    char saveLocation[MAX_PATH] = { 0 };
    SHGetSpecialFolderPathA(NULL, saveLocation, CSIDL_DESKTOPDIRECTORY, FALSE);

    std::string fullFilePath = std::string(saveLocation) + "\\" + fileName;
    std::ofstream newFile(fullFilePath);
    if (newFile.is_open()) {
        // Iterate through seenLines and write each line to the file
        for (const auto& line : seenLines) {
            // Convert wstring to narrow string
            std::string narrowLine(line.begin(), line.end());
            newFile << narrowLine << std::endl;
        }
        newFile.close(); // Close the file when done
    }
    else {
        std::cerr << "Failed to open file for writing!\n";
    }

    return counter; // int for the amount of duplicates removed
}