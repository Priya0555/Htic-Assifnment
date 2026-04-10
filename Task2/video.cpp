#include "video.h"
#include <QDebug>

void Video::run()
{
    running = true;
    cv::VideoCapture cap(0);

    if (!cap.isOpened()) return;

    cv::VideoWriter writer("output.avi",
                     cv::VideoWriter::fourcc('M','J','P','G'), 30,
                     cv::Size((int)cap.get(cv::CAP_PROP_FRAME_WIDTH),
                    (int)cap.get(cv::CAP_PROP_FRAME_HEIGHT)));

    cv::Mat frame;

    while (running) {
        cap >> frame;
        if (frame.empty()) continue;

        writer.write(frame);        //Save video

        emit frameReady(frame);     //Send to UI

        QThread::msleep(30);        //smooth + no freeze
    }

    cap.release();
    writer.release();
}

void Video::stop()
{
    running = false;
}