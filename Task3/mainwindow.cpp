#include "mainwindow.h"

#include <QMenuBar>
#include <QFileDialog>

MainWindow::MainWindow()
{
    canvas = new Canvas;
    setCentralWidget(canvas);

    auto fileMenu = menuBar()->addMenu("File");

    QAction *open = fileMenu->addAction("Open Image");
    QAction *save = fileMenu->addAction("Save JSON");
    QAction *load = fileMenu->addAction("Load JSON");

    connect(open, &QAction::triggered, [&]() {
        QString file = QFileDialog::getOpenFileName(this);
        canvas->loadImage(file);
    });

    connect(save, &QAction::triggered, [&]() {
        QString file = QFileDialog::getSaveFileName(this);
        canvas->saveJson(file);
    });

    connect(load, &QAction::triggered, [&]() {
        QString file = QFileDialog::getOpenFileName(this);
        canvas->loadJson(file);
    });
}