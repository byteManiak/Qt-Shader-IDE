#ifndef ABOUT_H
#define ABOUT_H

#include <QWidget>
#include <QWindow>
#include <QMainWindow>
#include <QTextBrowser>
#include <QLayout>

class About : public QMainWindow
{
    Q_OBJECT
public:
    explicit About(QWidget *parent = 0);

private:
    QTextBrowser *license;
};

#endif // ABOUT_H
