#include "file_sequence_finder_boost.h"

#include <boost/filesystem.hpp>

#include <exception>
#include <regex>
#include <iostream>
#include <optional>
#include <cstdlib>

namespace fs = boost::filesystem;

struct FileInfo
{
    std::string filePrefix;
    std::string fileNumber;
};

std::optional<FileInfo> getFileinfo(const std::string& filename)
{
    std::regex numbersRegex("([^0-9]*)([0-9]+)(.*)");

    auto numbersIter = std::sregex_iterator(filename.begin(), filename.end(), numbersRegex);

    if (std::distance(numbersIter, std::sregex_iterator()) < 1)
    {
        // if no number is contained in the filename, then return empty result.
        return {};
    }

    FileInfo info;

    info.filePrefix = numbersIter->str(1);
    info.fileNumber = numbersIter->str(2);

    return info;
}

std::vector<QString> FileSequenceFinderBoost::getFileSequence(const QString& inFilename)
{
    std::string file = inFilename.toStdString();

    fs::path initialFile(file);

    if (!fs::exists(initialFile))
    {
        throw std::runtime_error("File does not exist: " + file);
    }

    if (!fs::is_regular_file(initialFile))
    {
        throw std::runtime_error("File is not a regular file: " + file);
    }

    std::string filename = initialFile.filename().string();

    auto fileInfo = getFileinfo(filename);
    if (!fileInfo)
    {
        return {inFilename};
    }

    // Now iterate over directory
    auto fileDirectory = initialFile.parent_path();
    if (!fs::is_directory(fileDirectory))
    {
        throw std::runtime_error("Not a directory: " + fileDirectory.string());
    }

    std::map<long int, std::string> sequenceFiles;

    for (fs::directory_entry& x : fs::directory_iterator(fileDirectory))
    {
        auto info = getFileinfo(x.path().filename().string());
        if (info)
        {
            if (info->filePrefix == fileInfo->filePrefix)
            {
                long int number = strtol(info->fileNumber.c_str(), nullptr, 10);
                sequenceFiles[number] = x.path().string();
            }
        }
    }

    std::vector<QString> ret;

    for (auto& entry: sequenceFiles)
    {
        ret.push_back(QString::fromStdString(entry.second));
    }

    return ret;
}
