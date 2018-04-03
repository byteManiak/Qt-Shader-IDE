#ifndef IDE_H
#define IDE_H

#include <sstream>
#include <QWindow>
#include <QMainWindow>
#include <QTimer>
#include <QFileDialog>
#include <QStandardPaths>
#include "glwidget.h"
#include "glslsyntax.h"
#include "about.h"

namespace Ui {
class IDE;
}

class IDE : public QMainWindow
{
    Q_OBJECT

public:
    explicit IDE(QWidget *parent = 0);
    ~IDE();

private:
    Ui::IDE *ui;
    QTimer *timer;
    About *about;
    QString currentFile;
	GLWidget *openGLWidget;
	GLSLSyntax *vertexSyntaxHighlighter, *fragmentSyntaxHighlighter;

public slots:
    void open();
    void save();
	void sendStrings();
	void importTexture();
	void importModel();

signals:
    void strings(std::string, std::string);
	void pathToTexture(QString);
	void pathToModel(QString);
};

#endif // IDE_H
