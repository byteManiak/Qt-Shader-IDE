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

    connect(ui->actionRun, SIGNAL(triggered()), this, SLOT(compileShader()));
    connect(ui->actionReset, SIGNAL(triggered()), ui->openGLWidget, SLOT(reset()));
    connect(ui->actionBreak, SIGNAL(triggered()), ui->openGLWidget, SLOT(stop()));
    connect(ui->actionFragmentEditor, SIGNAL(triggered()), ui->fragPlainTextEdit, SLOT(toggle()));
    connect(ui->actionVertexEditor, SIGNAL(triggered()), ui->vertPlainTextEdit, SLOT(toggle()));
    connect(ui->actionContext, SIGNAL(triggered()), ui->openGLWidget, SLOT(toggle()));
    connect(ui->actionAbout, SIGNAL(triggered()), about, SLOT(show()));

    /** CONTEXT SPECIFIC **/

    connect(ui->openGLWidget, SIGNAL(resized()), ui->openGLWidget, SLOT(resizeGL()));
    connect(ui->toolBar->speed_slider, SIGNAL(valueChanged(int)), ui->openGLWidget, SLOT(speedGL(int)));

    /** ERROR OUTPUT **/

    ui->textBrowser->hide();
    connect(ui->openGLWidget, SIGNAL(noError()), ui->textBrowser, SLOT(close()));
    connect(ui->openGLWidget, SIGNAL(outputError(QString)), ui->textBrowser, SLOT(setText(QString)));
    connect(ui->textBrowser, SIGNAL(textChanged()), ui->textBrowser, SLOT(show()));
}

IDE::~IDE()
{
    delete ui;
}

void IDE::compileShader()
{
    if(ui->openGLWidget->isHidden()) ui->openGLWidget->show();
    ui->openGLWidget->compile(ui->vertPlainTextEdit->toPlainText(), ui->fragPlainTextEdit->toPlainText());
}
