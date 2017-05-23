#include "ide.h"
#include "ui_ide.h"

IDE::IDE(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::IDE)
{
    ui->setupUi(this);
    ui->splitter->setStretchFactor(0,1);
    ui->splitter->setStretchFactor(1,1);
    ui->splitter->setStretchFactor(2,1);

    ui->splitter_2->setStretchFactor(0, 2);
    ui->splitter_2->setStretchFactor(1, 1);
    timer = new QTimer(this);
    timer->start();

    connect(timer, SIGNAL(timeout()), ui->openGLWidget, SLOT(update()));

    about = new About();

    /** MENU ACTIONS **/

    connect(ui->actionFragmentEditor, SIGNAL(triggered()), ui->fragPlainTextEdit, SLOT(toggle()));
    connect(ui->actionVertexEditor, SIGNAL(triggered()), ui->vertPlainTextEdit, SLOT(toggle()));
    connect(ui->actionAbout, SIGNAL(triggered()), about, SLOT(show()));

    /** CONTEXT SPECIFIC **/



    /** ERROR OUTPUT **/

    ui->textBrowser->hide();
    connect(ui->textBrowser, SIGNAL(textChanged()), ui->textBrowser, SLOT(show()));
}

IDE::~IDE()
{
    timer->stop();
    delete timer;
    delete about;
    delete ui;
}
