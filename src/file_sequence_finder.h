#ifndef FILE_SEQUENCE_FINDER_H
#define FILE_SEQUENCE_FINDER_H

#include <vector>
#include <QString>

class FileSequenceFinder
{
public:
    virtual ~FileSequenceFinder();
    virtual std::vector<QString> getFileSequence(const QString& filename) = 0;
};

#endif // FILE_SEQUENCE_FINDER_H
