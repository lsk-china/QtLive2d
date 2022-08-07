//
// Created by lsk on 7/25/22.
//

#ifndef QTLIVE2D_MAINWINDOW_H
#define QTLIVE2D_MAINWINDOW_H

#define QCOREEVENT_H
#define QVARIANT_H
#define QTEXTSTREAM_H

#include <QMainWindow>
#include <QWidget>
#include <QtX11Extras/QX11Info>
#include <QPoint>
#include <X11/extensions/shape.h>
#include "mouseEventThread.h"
#include "../QtLive2d/QLive2dWidget.hpp"
#include "iostream"
using namespace std;

class MainWindow : public QMainWindow{
    Q_OBJECT
public:
    QLive2dWidget *live2DWidget;
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void initialized(QLive2dWidget *wid);
    void mouseEvent(QPoint rel, QPoint abs);
//    void mouseEvent(QPoint relPosition, QPoint absPosition);
};


#endif //QTLIVE2D_MAINWINDOW_H
