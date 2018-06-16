#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSettings>
#include <QGraphicsScene>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    virtual ~MainWindow();

public slots:
    void displayImage(QImage pixmap);
    void setFrameSlider(int frame, int frameCount);

signals:
    void selectFrame(int frame);
    void openFile(QString filename);

private:
    Ui::MainWindow *ui;

    QSettings m_settings;
    QGraphicsScene m_scene;
    QGraphicsPixmapItem* m_pixmapItem;
};

#endif // MAINWINDOW_H
