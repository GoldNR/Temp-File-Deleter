#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

void deleteFolder(const fs::path& folderPath) {
    for (const auto& entry : fs::directory_iterator(folderPath)) {
        try {
            if (fs::is_directory(entry)) {
                deleteFolder(entry.path());
            }
            else {
                fs::remove(entry);
            }
        }
        catch (const fs::filesystem_error& ex) {
            std::cerr << "Error deleting file: " << entry.path().string() << std::endl;
            std::cerr << "Reason: " << ex.what() << std::endl << std::endl;
        }
    }

    fs::remove(folderPath);
}

int main() {
    const fs::path tempFolderPath = fs::temp_directory_path();

    try {
        deleteFolder(tempFolderPath);
        std::cout << "All files and folders in the temp folder have been deleted." << std::endl << std::endl;
    }
    catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << std::endl << std::endl;
    }

    std::cout << "Press Enter to exit...";
    std::cin.get();

    return 0;
}
