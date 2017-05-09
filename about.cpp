#include "about.h"

About::About(QWidget *parent) : QMainWindow(parent)
{
    QHBoxLayout *layout = new QHBoxLayout();
    setWindowTitle("About QT_IDE");
    license = new QTextBrowser(this);
    layout->addWidget(license);
}
