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
	connect(ui->actionContext, SIGNAL(triggered()), ui->openGLWidget, SLOT(toggle()));
    connect(ui->actionAbout, SIGNAL(triggered()), about, SLOT(show()));
    connect(ui->actionExit, SIGNAL(triggered()), about, SLOT(close()));
    connect(ui->actionRun, SIGNAL(triggered()), this, SLOT(sendStrings()));
    connect(ui->actionReset, SIGNAL(triggered()), ui->openGLWidget, SLOT(reset()));
	connect(ui->actionBreak, SIGNAL(triggered()), ui->openGLWidget, SLOT(close()));

    /** CONTEXT SPECIFIC **/

    connect(this, SIGNAL(strings(std::string,std::string)),
            ui->openGLWidget, SLOT(compileShader(std::string,std::string)));

    /** ERROR OUTPUT **/

    ui->textBrowser->hide();
    connect(ui->openGLWidget, SIGNAL(shaderError(QString)), ui->textBrowser, SLOT(setPlainText(QString)));
    connect(ui->textBrowser, SIGNAL(textChanged()), ui->textBrowser, SLOT(show()));
}

void IDE::sendStrings()
{
	ui->textBrowser->hide();
	ui->openGLWidget->show();
	emit strings( ui->vertPlainTextEdit->toPlainText().toStdString(),
				  ui->fragPlainTextEdit->toPlainText().toStdString() );
}

IDE::~IDE()
{
    timer->stop();
    delete timer;
    delete about;
    delete ui;
}
