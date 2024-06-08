#ifndef MOUSEEVENTTHREAD_H
#define MOUSEEVENTTHREAD_H

#include <X11/X.h>
#include <X11/Xlibint.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/XKBlib.h>
#include <X11/cursorfont.h>
#include <X11/keysymdef.h>
#include <X11/keysym.h>
#include <X11/extensions/record.h>
#include <X11/extensions/XTest.h>

#undef Bool
#undef CursorShape
#undef Expose
#undef KeyPress
#undef KeyRelease
#undef FocusIn
#undef FocusOut
#undef FontChange
#undef None
#undef Status
#undef Unsorted
#undef min
#undef max

#include <QApplication>
#include <QThread>
#include <QDebug>
#include <QObject>
#include <QX11Info>
#include <QRect>
#include <QPoint>

#define WheelUp			4
#define WheelDown		5
#define WheelLeft		6
#define WheelRight		7

typedef union {
    unsigned char    type ;
    xEvent           event ;
    xResourceReq     req   ;
    xGenericReply    reply ;
    xError           error ;
    xConnSetupPrefix setup;
} XRecordDatum;

using namespace std;

class MouseEventThread : public QThread {
Q_OBJECT
public:
    MouseEventThread(QRect screenRect, int winID, double sensibility, QObject *parent = nullptr);
    ~MouseEventThread();
    static void callback(XPointer closure, XRecordInterceptData* hook);
    void processEvent(XRecordInterceptData* hook);
    int queryCursor(int &relX, int &relY, int &absX, int &absY);
    void setMouseSensibility(double mouseSensibility);

public slots:
    void cleanup();

private:
    void run() override;


    Display *controlDisplay;
    Display *dataDisplay;
    XRecordContext ctx;
    XRecordRange *rr;
    Window rootWindow;
    Window appWindow;
    double sensibility;
//    int dx, dy, lastx, lasty = 0;
signals:
    void mouseEvent(QPoint relPosition, QPoint rawPosition);
    void mousePress(QPoint relPosition, QPoint rawPosition);
    void mouseRelease(QPoint relPosition, QPoint rawPosition);
};


#endif // MOUSEEVENTTHREAD_H
