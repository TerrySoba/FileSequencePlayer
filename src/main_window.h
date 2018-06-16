#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSettings>
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
    void displayImage(QPixmap pixmap);
    void setFrameSlider(int frame, int frameCount);

signals:
    void selectFrame(int frame);
    void openFile(QString filename);

private:
    Ui::MainWindow *ui;

    QSettings m_settings;

};

#endif // MAINWINDOW_H
