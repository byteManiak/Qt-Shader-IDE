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
    QTimer *timer;
    About *about;
};

#endif // IDE_H
