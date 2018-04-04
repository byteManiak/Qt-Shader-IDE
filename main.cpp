#include "ide.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QSurfaceFormat format;
	format.setVersion(3, 3);	// set context to GL 3.3
	format.setProfile(QSurfaceFormat::CoreProfile);	// set context to core profile
	format.setSwapInterval(1);	// ensure that vsync is enabled
	QSurfaceFormat::setDefaultFormat(format);	// apply the settings above
	QCoreApplication::addLibraryPath(".");	// if libraries exist in the current folder, look for them
    QApplication a(argc, argv);
    IDE w;
    w.show();

    return a.exec();
}
