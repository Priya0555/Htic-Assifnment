#ifndef VIDEO_H
#define VIDEO_H

#include <QWidget>
#include <QThread>
#include <opencv2/opencv.hpp>

class Video : public QThread
{
    Q_OBJECT
 public:

    void run() override;
    void stop();

signals:
    void frameReady(cv::Mat frame);

private:
    bool running = false;
};

#endif // VIDEO_H
