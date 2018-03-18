#ifndef IDE_H
#define IDE_H

#include <sstream>
#include <QWindow>
#include <QMainWindow>
#include <QTimer>
#include <QFileDialog>
#include <QStandardPaths>
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

public slots:
    void open();
    void save();
    void sendStrings();

signals:
    void strings(std::string, std::string);
};

#endif // IDE_H
