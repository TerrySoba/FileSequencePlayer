#include "main_window.h"
#include "ui_main_window.h"

#include <QFileDialog>
#include <QGraphicsPixmapItem>

#include <algorithm>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_settings("MySoft", "FileSequencePlayer")
{
    ui->setupUi(this);

    ui->frameSlider->setMinimum(0);
    ui->frameSlider->setMaximum(0);

    connect(ui->nextFrameButton, &QPushButton::clicked, ui->frameSlider, [this]()
    {
        auto value = std::min(ui->frameSlider->value() + 1, ui->frameSlider->maximum());
        ui->frameSlider->setValue(value);
    });

    connect(ui->prevFrameButton, &QPushButton::clicked, ui->frameSlider, [this]()
    {
        auto value = std::max(ui->frameSlider->value() - 1, ui->frameSlider->minimum());
        ui->frameSlider->setValue(value);
    });

    connect(ui->actionOpen, &QAction::triggered, this, [this]()
    {
        QString lastDir = this->m_settings.value("files/lastOpen", "").toString();
        QString filename = QFileDialog::getOpenFileName(this, tr("Select Image File"), lastDir, tr("Images (*.png *.jpg)"));
        this->m_settings.setValue("files/lastOpen", filename);
        emit this->openFile(filename);
    });

    connect(ui->frameSlider, &QSlider::valueChanged, this, &MainWindow::selectFrame);

    m_pixmapItem = m_scene.addPixmap(QPixmap());

    ui->graphicsView->setScene(&m_scene);

}

MainWindow::~MainWindow()
{
    m_settings.sync();
    delete ui;
}

void MainWindow::displayImage(QImage image)
{
    // ui->videoLabel->setPixmap(pixmap);

    m_pixmapItem->setPixmap(QPixmap::fromImage(image));

}

void MainWindow::setFrameSlider(int frame, int frameCount)
{
    ui->frameSlider->setMinimum(0);
    ui->frameSlider->setMaximum(frameCount - 1);
    ui->frameSlider->setValue(frame);
}
