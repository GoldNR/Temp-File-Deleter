#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

void deleteFolder(const fs::path& folderPath)
{
    for (const auto& entry : fs::directory_iterator(folderPath))
    {
        try
        {
            if (fs::is_directory(entry))
            {
                deleteFolder(entry.path());
            }
            else
            {
                fs::remove(entry);
            }
        }
        catch (const fs::filesystem_error& ex)
        {
            std::cerr << "Error deleting file: " << entry.path().string() << '\n';
            std::cerr << "Reason: " << ex.what() << '\n';
        }
    }

    fs::remove(folderPath);
}

int main()
{
    const fs::path tempFolderPath = fs::temp_directory_path();

    try
    {
        deleteFolder(tempFolderPath);
        std::cout << "All files and folders in the temp folder have been deleted.\n";
    }
    catch (const std::exception& ex)
    {
        std::cerr << "Error: " << ex.what() << '\n';
    }

    return 0;
}