#include "gltoolbar.h"

GLToolBar::GLToolBar(QWidget *parent) : QToolBar(parent)
{
    speed_slider = new QSlider(Qt::Horizontal);
    speed_slider->setFixedWidth(100);
    speed_slider->setTickPosition(QSlider::TicksBothSides);
    speed_slider->setRange(0, 8);
    speed_slider->setValue(1);

    addWidget(new QLabel("Context Speed:"));
    addWidget(speed_slider);
    addSeparator();
}
