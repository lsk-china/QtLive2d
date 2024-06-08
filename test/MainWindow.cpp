//
// Created by lsk on 7/25/22.
//

#include "MainWindow.h"
#include <QThread>



MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    this->live2DWidget = new QLive2dWidget(this);
    connect(this->live2DWidget, SIGNAL(initialized(QLive2dWidget*)), this, SLOT(initialized(QLive2dWidget*)));
    this->setCentralWidget(this->live2DWidget);
    this->resize(763, 495);
//    XShapeCombineRectangles(QX11Info::display(),
//                            this->winId(),
//                            ShapeInput, 0, 0, nullptr, 0, ShapeSet, YXBanded);
//    this->live2DWidget->setResDir("Resources");
//    this->live2DWidget->setModel("WY6");
//    this->live2DWidget->setAttribute(Qt::WA_TransparentForMouseEvents);
    MouseEventThread *th = new MouseEventThread(this->geometry(), this->winId(), 0.1, this);
    connect(th, SIGNAL(mouseEvent(QPoint, QPoint)), this, SLOT(mouseEvent(QPoint, QPoint)), Qt::QueuedConnection);
    th->start();
}

MainWindow::~MainWindow() {
    delete live2DWidget;
}

void MainWindow::initialized(QLive2dWidget *wid) {
    wid->setResDir("/data/Live2dModels/");
    wid->setModel("guiz");
    cout<<"Initialize finished";
}

void MainWindow::mouseEvent(QPoint relPosition, QPoint absPosition) {
    this->live2DWidget->mouseMove(relPosition);
}