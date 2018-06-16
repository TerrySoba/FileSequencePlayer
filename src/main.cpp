#include "main_window.h"
#include "main_window_controller.h"
#include "file_sequence_finder_boost.h"

#include <QApplication>
#include <QThread>

#include <memory>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    auto fileSequenceFinder = std::make_shared<FileSequenceFinderBoost>();

    QThread thread;

    MainWindowController controller(fileSequenceFinder);

    controller.moveToThread(&thread);

    MainWindow win;

    QObject::connect(&win, &MainWindow::openFile, &controller, &MainWindowController::openFile);
    QObject::connect(&win, &MainWindow::selectFrame, &controller, &MainWindowController::selectFrame);
    QObject::connect(&controller, &MainWindowController::displayImage, &win, &MainWindow::displayImage);
    QObject::connect(&controller, &MainWindowController::imagesLoaded, &win, &MainWindow::setFrameSlider);

    win.show();

    thread.start();
    auto ret = a.exec();

    thread.exit();
    thread.wait();

    return ret;
}
