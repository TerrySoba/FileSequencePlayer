#include "main_window_controller.h"

#include <QPixmap>
#include <QThreadPool>
#include <QMutex>
#include <QSemaphore>

#include <iostream>
#include <algorithm>

MainWindowController::MainWindowController(std::shared_ptr<FileSequenceFinder> fileSequenceFinder) :
    m_fileSequenceFinder(fileSequenceFinder)
{

}

void MainWindowController::selectFrame(int frame)
{
    if (frame >= 0 && frame < m_images.size())
    {
        emit displayImage(m_images[frame]);
    }
}


class FileLoaderThread : public QRunnable
{
public:
    FileLoaderThread(QSemaphore& semaphore,
                     std::vector<QImage>& results,
                     std::vector<QString>::iterator begin,
                     std::vector<QString>::iterator end) :
        m_semaphore(semaphore),
        m_results(results),
        m_begin(begin),
        m_end(end)
    {

    }

    virtual void run() override
    {
        while (m_begin != m_end)
        {
            m_results.push_back(QImage(*m_begin));
            m_semaphore.release(1);
            ++m_begin;
        }
    }

private:
    QSemaphore& m_semaphore;
    std::vector<QImage>& m_results;
    std::vector<QString>::iterator m_begin;
    std::vector<QString>::iterator m_end;
};


void MainWindowController::openFile(QString filename)
{
    auto files = m_fileSequenceFinder->getFileSequence(filename);
    if (!files.empty())
    {
        QImage pix(files.at(0));
        emit displayImage(pix);
    }

    m_images.clear();

    auto threadCount = QThreadPool::globalInstance()->maxThreadCount();

    std::cout << "Using threads: " << threadCount << std::endl;

    std::vector<std::vector<QImage>> threadResults(threadCount);
    QSemaphore semaphore(0);

    int elements = std::max(1, static_cast<int>(files.size()) / threadCount);
    auto filesIter = files.begin();

    for (int i = 0; i < threadCount; ++i)
    {
        auto dist = std::min(elements + 1, static_cast<int>(std::distance(filesIter, files.end())));
        auto nextfilesIter = filesIter + dist;
        QThreadPool::globalInstance()->start(
                    new FileLoaderThread(
                        semaphore,
                        threadResults[i],
                        filesIter,
                        nextfilesIter));

        filesIter = nextfilesIter;
    }

    int framesDone = 0;

    // wait for all images to have been processed
    for (int i = 0; i < files.size(); ++i)
    {
        semaphore.acquire(1);
        ++framesDone;
        emit progress(((double)framesDone / files.size()) * 100);
    }

    for (auto& result : threadResults)
    {
        m_images.insert(m_images.end(), result.begin(), result.end());
    }

    m_currentFrame = 0;
    emit imagesLoaded(m_currentFrame, static_cast<int>(files.size()));
}

