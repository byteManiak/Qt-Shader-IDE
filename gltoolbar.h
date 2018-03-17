#ifndef GLTOOLBAR_H
#define GLTOOLBAR_H

#include <QWidget>
#include <QToolBar>
#include <QLabel>
#include <QSlider>
#include <QComboBox>

class GLToolBar : public QToolBar
{
    Q_OBJECT
public:
    explicit GLToolBar(QWidget *parent = 0);
    ~GLToolBar() {}
};

#endif // GLTOOLBAR_H
