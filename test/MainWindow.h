//
// Created by lsk on 7/25/22.
//

#ifndef QTLIVE2D_MAINWINDOW_H
#define QTLIVE2D_MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QtX11Extras/QX11Info>
#include <QPoint>
#include <QMouseEvent>
//#include <X11/extensions/shape.h>
//#include "mouseEventThread.h"
#include "../QtLive2d/QLive2dWidget.hpp"

class MainWindow : public QMainWindow{
    Q_OBJECT
public:
    QLive2dWidget *live2DWidget;
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
protected:
    inline void mouseMoveEvent(QMouseEvent *ev) override {
        this->live2DWidget->mouseMove(ev);
    }
public slots:
    void initialized(QLive2dWidget *wid);
//    void mouseEvent(QPoint relPosition, QPoint absPosition);
};


#endif //QTLIVE2D_MAINWINDOW_H
