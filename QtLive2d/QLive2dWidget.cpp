#include "QLive2dWidget.hpp"
#include <QApplication>
#include "openglhelper.hpp"
#include "LAppDelegate.hpp"
#include "LAppView.hpp"
#include <QTimer>
#include "LAppDefine.hpp"
#include "LAppLive2DManager.hpp"
#include <QDebug>
#include <Motion/ACubismMotion.hpp>
#include <Type/csmMap.hpp>

LAppDelegate *appDelegateInstance = LAppDelegate::GetInstance();
LAppLive2DManager *appLive2DManagerInstance = LAppLive2DManager::GetInstance();

QLive2dWidget::QLive2dWidget(QWidget *parent):
    QOpenGLWidget(parent)
{
    this->setAttribute(Qt::WA_AlwaysStackOnTop);
    this->setAttribute(Qt::WA_TranslucentBackground);

    elapsedTimer.start();

    //Add the render into Timer to make the animation
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &QLive2dWidget::updateMotions);
    timer->start(1);

    // the OpenGL in OpenGLWidget won't scale by HDPI setting, we need to scale manually.
    ratio = parent->devicePixelRatio();
    calcRatios();
    appLive2DManagerInstance->OnUpdate();
}

void QLive2dWidget::calcRatios() {
    QWidget* parent = this->parentWidget();
    if (parent != nullptr) {
        QSize parentSize = parent->size();
        QSize thisSize = this->size();
        ratio_x = thisSize.width() / parentSize.width();
        ratio_y = thisSize.height() / parentSize.height();
        ratio_x *= ratio;
        ratio_y *= ratio;
    } else {
        ratio_x = ratio_y = ratio;
    }
    cout << "ratio_x: " << ratio_x << endl;
    cout << "ratio_y: " << ratio_y << endl;
    cout << "ratio: " << ratio << endl;
}

void QLive2dWidget::initializeGL()
{
    this->makeCurrent();
    OpenGLHelper::init(this->context());

    appDelegateInstance->Initialize(this);
    appDelegateInstance->Run();

    OpenGLHelper::get()->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    OpenGLHelper::get()->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    OpenGLHelper::get()->glEnable(GL_BLEND);
    OpenGLHelper::get()->glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    appDelegateInstance->_view->OnTouchesBegan(0, 0);
    this->initialized(this);
}
void QLive2dWidget::resizeGL(int width, int height)
{
    appDelegateInstance->Resize(width*ratio,height*ratio);
}

void QLive2dWidget::paintGL()
{
    appDelegateInstance->Run();
}

void QLive2dWidget::clear()
{
    OpenGLHelper::get()->glViewport(0, 0, width()*ratio, height()*ratio);
    OpenGLHelper::get()->glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    OpenGLHelper::get()->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    OpenGLHelper::get()->glClearDepthf(1.0);
}


void QLive2dWidget::updateMotions()
{
    update();
}

void QLive2dWidget::mouseMove(QPoint rel) {
    appDelegateInstance->rawMouseMoveEvent(rel);
}

void QLive2dWidget::setModel(string model) {
    this->clear();
    appLive2DManagerInstance->ChangeModel(model, this->resourceDir);
    appLive2DManagerInstance->OnUpdate();
    appDelegateInstance->Run();
}
void QLive2dWidget::setResDir(string resDir) {
    this->resourceDir = resDir;
}

void QLive2dWidget::mouseMoveEvent(QMouseEvent * event){
    appDelegateInstance->mouseMoveEvent(event);
}
void QLive2dWidget::mousePressEvent(QMouseEvent * event){
    appDelegateInstance->mousePressEvent(event);
}
void QLive2dWidget::mouseReleaseEvent(QMouseEvent * event){
    appDelegateInstance->mouseReleaseEvent(event);
}
void QLive2dWidget::mousePress(QPoint rel) {
    appDelegateInstance->rawMousePressEvent(rel);
}
void QLive2dWidget::mouseRelease(QPoint rel) {
    appDelegateInstance->rawMouseReleaseEvent(rel);
}

void QLive2dWidget::changeExpression(const QString& name) {
    appLive2DManagerInstance->SetExpression(name.toStdString().c_str());
    appLive2DManagerInstance->OnUpdate();
}

QList<QString> QLive2dWidget::getExpressions() {
    QList<QString> result;
//    for (int i = 0; i < LAppLive2DManager::GetInstance()->GetExpressionCount(); i++) {
//        result.push_back(QString(LAppLive2DManager::GetInstance()->GetExpressions().get(i).First.GetRawString()));
//    }
    for (auto entry : appLive2DManagerInstance->GetExpressionNames()) {
        result.push_back(QString::fromStdString(entry));
    }
    return result;
}
