#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include "video.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
      MainWindow();
      ~MainWindow();
private slots:
    void updateFrame(cv::Mat frame);
    void startCamera();
    void stopCamera();
    void takeSnapshot();

private:
    QLabel *videoLabel;
    QPushButton *startBtn;
    QPushButton *stopBtn;
    QPushButton *snapBtn;

    Video *worker;
    cv::Mat currentFrame;
};

#endif // MAINWINDOW_H