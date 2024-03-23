#include <iostream>
#include <Windows.h>
#include <fstream>

#include "fileDialog.h" // open files
#include "checkCombo.h" // check if its set-up correctly!
#include "passwordManager.h" // check dupes

int main(int argc, char* argv[]) {
    if (argc <= 1) {
        std::wcerr << "Failed to obtain argument for result file, please use '" << argv[0] << " output.txt'\n";
        return 1;
    }

    std::cout << "Welcome to the combo checker!\nPlease make sure your first line is blank!\n";
    std::cout << "Please select a file...\n";

    std::wstring file = openFileDialog();
    std::vector<std::wstring> fileContent = getFileContent(file);

    system("cls");
    std::cout << "Loading " << fileContent.size() << " accounts to check.\n";

    if (!hasNewLine(file)) {
        std::cerr << "Please enter a blank line at the beginning of your combo.\nIf you have a blank line, please exit the file.\n";
        return 1;
    }

    int count = hasDuplicates(fileContent, argv[1]);

    std::cout << "You have " << count << " duplicates detected / removed!\n";
    std::cout << "Please re-open your file to see the changes!\n";

    return 0;
}
