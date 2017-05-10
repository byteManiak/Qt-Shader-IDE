#ifndef IDE_H
#define IDE_H

#include <QWindow>
#include <QMainWindow>
#include <QTimer>
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
    QTextBrowser *error_output;
    QTimer *timer;
    QWindow *GLcontext;
    About *about;

public slots:
    void compileShader();
};

#endif // IDE_H
