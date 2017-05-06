#include "ide.h"
#include "ui_ide.h"

IDE::IDE(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::IDE)
{
    ui->setupUi(this);
    ui->splitter->setStretchFactor(0,1);
    ui->splitter->setStretchFactor(1,1);
    timer = new QTimer(this);
    timer->start();
    ui->openGLWidget->hide();
    connect(timer, SIGNAL(timeout()), ui->openGLWidget, SLOT(update()));
    connect(ui->actionRun, SIGNAL(triggered()), ui->openGLWidget, SLOT(show()));
    connect(ui->actionBreak, SIGNAL(triggered()), ui->openGLWidget, SLOT(close()));
}

IDE::~IDE()
{
    delete ui;
}
