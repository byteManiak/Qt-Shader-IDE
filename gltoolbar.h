#ifndef GLTOOLBAR_H
#define GLTOOLBAR_H

#include <QWidget>
#include <QToolBar>
#include <QLabel>
#include <QSlider>

class GLToolBar : public QToolBar
{
    Q_OBJECT
public:
    explicit GLToolBar(QWidget *parent = 0);
    QSlider *speed_slider;
    ~GLToolBar() { delete speed_slider; }
};

#endif // GLTOOLBAR_H
