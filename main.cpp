#include "ide.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QSurfaceFormat format;
    format.setVersion(3, 3);
    format.setProfile(QSurfaceFormat::CoreProfile);
    QSurfaceFormat::setDefaultFormat(format);
    QCoreApplication::addLibraryPath(".");
    QApplication a(argc, argv);
    IDE w;
    w.show();

    return a.exec();
}
