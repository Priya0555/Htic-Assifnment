#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "canvas.h"
#include <QMainWindow>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();

private:
    Canvas *canvas;
};

#endif // MAINWINDOW_H
