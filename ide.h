#ifndef IDE_H
#define IDE_H

#include <QWindow>
#include <QMainWindow>
#include <QTimer>

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
    QTimer *timer;
    QWindow *GLcontext;
    Ui::IDE *ui;

public slots:
    void compileShader();
};

#endif // IDE_H
