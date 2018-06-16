#include "main_window_controller.h"

#include <QPixmap>

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



void MainWindowController::openFile(QString filename)
{
    auto files = m_fileSequenceFinder->getFileSequence(filename);
    if (!files.empty())
    {
        QPixmap pix(files.at(0));
        emit displayImage(pix);
    }

    for (auto& file : files)
    {
        m_images.push_back(QPixmap(file));
    }

    m_currentFrame = 0;
    emit imagesLoaded(m_currentFrame, static_cast<int>(files.size()));
}

