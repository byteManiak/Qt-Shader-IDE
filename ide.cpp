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

	currentFile = QStandardPaths::locate(QStandardPaths::HomeLocation, QString(),
											  QStandardPaths::LocateDirectory);

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
	connect(ui->actionOpen, SIGNAL(triggered()), this, SLOT(open()));
	connect(ui->actionSave, SIGNAL(triggered()), this, SLOT(save()));

    /** CONTEXT SPECIFIC **/

    connect(this, SIGNAL(strings(std::string,std::string)),
            ui->openGLWidget, SLOT(compileShader(std::string,std::string)));

    /** ERROR OUTPUT **/

    ui->textBrowser->hide();
    connect(ui->openGLWidget, SIGNAL(shaderError(QString)), ui->textBrowser, SLOT(setPlainText(QString)));
    connect(ui->textBrowser, SIGNAL(textChanged()), ui->textBrowser, SLOT(show()));
}

void IDE::open()
{
	ui->openGLWidget->close();
	// not closing the GL widget causes the file dialog to be invisible - at least on my machine

	currentFile = QFileDialog::getOpenFileName(this, "Open GLSL file", currentFile,
										"GLSL files (*.glsl);;Any files(*.*)"); // get file path
	QFile file(currentFile); // get file handle

	if(file.open(QFile::ReadOnly)) // see if file can be opened properly
	{
		ui->fragPlainTextEdit->clear();
		ui->vertPlainTextEdit->clear();
		// clear editors first

		QTextStream inputStream(&file); // get file contents
		QString line = inputStream.readLine(); // get first line

		if(line == "GLSL_FILE") // check if file is a valid IDE-formatted file
		{
			line = inputStream.readLine();
			if(line == "VERTEX_SHADER_BEGIN") // check if vertex shader exists
			{
				line = inputStream.readLine();
				while(line != "VERTEX_SHADER_END") // if not reached end of vertex shader, write to editor
				{
					ui->vertPlainTextEdit->appendPlainText(line);
					line = inputStream.readLine();
				}
			}

			line = inputStream.readLine();
			line = inputStream.readLine();
			// there is a one-line gap between "VERTEX_SHADER_END" and "FRAGMENT_SHADER_BEGIN"

			if(line == "FRAGMENT_SHADER_BEGIN") // same as above but for fragment shader
			{
				line = inputStream.readLine();
				while(line != "FRAGMENT_SHADER_END")
				{
					ui->fragPlainTextEdit->appendPlainText(line);
					line = inputStream.readLine();
				}
			}
		}
		file.close(); // finally, close the file
	}
	std::cout << "Here we are" << std::endl;
}

void IDE::save()
{
	ui->openGLWidget->close();
	currentFile = QFileDialog::getSaveFileName(this, "Open GLSL file", currentFile,
										"GLSL files (*.glsl);;Any files(*.*)");
	QFile file(currentFile);
	if(file.open(QFile::WriteOnly))
	{
		QTextStream outputStream(&file);
		outputStream << "GLSL_FILE\n";
		outputStream << "VERTEX_SHADER_BEGIN\n";
		outputStream << ui->vertPlainTextEdit->toPlainText();
		outputStream << "\nVERTEX_SHADER_END\n\n";
		outputStream << "FRAGMENT_SHADER_BEGIN\n";
		outputStream << ui->fragPlainTextEdit->toPlainText();
		outputStream << "\nFRAGMENT_SHADER_END\n\n";
		file.close();
	}
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
