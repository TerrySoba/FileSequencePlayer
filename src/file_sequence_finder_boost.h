#ifndef FILE_SEQUENCE_FINDER_BOOST_H
#define FILE_SEQUENCE_FINDER_BOOST_H

#include "file_sequence_finder.h"
#include <QString>
#include <vector>


class FileSequenceFinderBoost : public FileSequenceFinder
{
public:
    virtual std::vector<QString> getFileSequence(const QString& filename) override;
};

#endif // FILE_SEQUENCE_FINDER_BOOST_H
