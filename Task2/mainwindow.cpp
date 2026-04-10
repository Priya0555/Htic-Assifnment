#include "mainwindow.h"
#include <QVBoxLayout>
#include <QImage>
#include <QPixmap>
#include <QDateTime>
#include <QDebug>
MainWindow::MainWindow()
{
    QWidget *central = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout;

    videoLabel = new QLabel;
    videoLabel->setFixedSize(640, 480);

    startBtn = new QPushButton("Start");
    stopBtn = new QPushButton("Stop");
    snapBtn = new QPushButton("Snapshot");

    layout->addWidget(videoLabel);
    layout->addWidget(startBtn);
    layout->addWidget(stopBtn);
    layout->addWidget(snapBtn);

    central->setLayout(layout);
    setCentralWidget(central);

    worker = new Video;

    connect(worker, &Video::frameReady,
            this, &MainWindow::updateFrame);

    connect(startBtn, &QPushButton::clicked,
            this, &MainWindow::startCamera);

    connect(stopBtn, &QPushButton::clicked,
            this, &MainWindow::stopCamera);

    connect(snapBtn, &QPushButton::clicked,
            this, &MainWindow::takeSnapshot);
}


MainWindow::~MainWindow()
{
    worker->stop();
    worker->wait();
    delete worker;
}

void MainWindow::startCamera()
{
    worker->start();
}

void MainWindow::stopCamera()
{
    worker->stop();
    worker->wait();
}

void MainWindow::updateFrame(cv::Mat frame)
{
    currentFrame = frame.clone();

    cv::cvtColor(frame, frame, cv::COLOR_BGR2RGB);

    QImage img(frame.data, frame.cols, frame.rows,
               frame.step, QImage::Format_RGB888);

    videoLabel->setPixmap(QPixmap::fromImage(img));
}

void MainWindow::takeSnapshot()
{
    if (currentFrame.empty()) return;

    QString name = "snapshot_" +
                   QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss") +
                   ".png";

    cv::imwrite(name.toStdString(), currentFrame);
}




