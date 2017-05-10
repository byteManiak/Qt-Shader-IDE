#include "about.h"

About::About(QWidget *parent) : QWidget(parent)
{
    setGeometry(0, 0, 640, 480);
    setWindowTitle("About this IDE");

    layout = new QVBoxLayout(this);

    layout->addWidget(new QLabel("This IDE is licensed under the LGPLv3 license:"));

    license = new QTextBrowser();
    f.open("LICENSE");
    std::string content( (std::istreambuf_iterator<char>(f) ),
                           (std::istreambuf_iterator<char>()    ) );
    license->setText(QString::fromStdString(content));
    f.close();
    layout->addWidget(license);
}
