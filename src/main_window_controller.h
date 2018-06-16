#ifndef MAIN_WINDOW_CONTROLLER_H
#define MAIN_WINDOW_CONTROLLER_H

#include "file_sequence_finder.h"

#include <QObject>

#include <memory>
#include <list>

class MainWindowController : public QObject
{
    Q_OBJECT
public:
    MainWindowController(std::shared_ptr<FileSequenceFinder> fileSequenceFinder);

public slots:
    void selectFrame(int frame);
    void openFile(QString filename);

signals:
    void displayImage(QImage image);
    void imagesLoaded(int currentFrame, int frameCount);
    void progress(int percent);

private:
    std::shared_ptr<FileSequenceFinder> m_fileSequenceFinder;
    std::vector<QImage> m_images;
    int m_currentFrame = 0;
};

#endif // MAIN_WINDOW_CONTROLLER_H
