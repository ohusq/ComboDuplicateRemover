#pragma once

#include <Windows.h>
#include <ShObjIdl.h>
#include <fstream>
#include <sstream>
#include <vector>

std::wstring openFileDialog() {
    std::wstring selectedFilePath;

    // Initialize COM library
    HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
    if (FAILED(hr)) {
        return selectedFilePath; // Return empty string if COM initialization fails
    }

    // Initialize COM object
    IFileOpenDialog* pFileOpen;
    hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL, IID_IFileOpenDialog, reinterpret_cast<void**>(&pFileOpen));
    if (FAILED(hr)) {
        CoUninitialize(); // Uninitialize COM before returning
        return selectedFilePath; // Return empty string if object creation fails
    }

    // Show the file dialog
    hr = pFileOpen->Show(NULL);
    if (SUCCEEDED(hr)) {
        // Get the selected file
        IShellItem* pItem;
        hr = pFileOpen->GetResult(&pItem);
        if (SUCCEEDED(hr)) {
            PWSTR pszFilePath;
            hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);
            if (SUCCEEDED(hr)) {
                // Use pszFilePath as the selected file path
                selectedFilePath = pszFilePath;
                CoTaskMemFree(pszFilePath);
            }
            pItem->Release();
        }
    }

    pFileOpen->Release();

    // unload
    CoUninitialize();

    return selectedFilePath;
}

std::vector<std::wstring> getFileContent(const std::wstring& filePath) {
    std::wifstream inputFile(filePath);
    std::wstring line;
    std::vector<std::wstring> fileContent; // L"Fourth line"


    while (std::getline(inputFile, line)) {
        // Add the account to the vector
        fileContent.push_back(line);
    }
    return fileContent;
}
