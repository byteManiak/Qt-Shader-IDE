#include "ide.h"
#include "ui_ide.h"

IDE::IDE(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::IDE)
{
    ui->setupUi(this);
    ui->splitter->setStretchFactor(0,1);
	ui->splitter->setStretchFactor(1,1);

	ui->splitter_2->setStretchFactor(0, 1);
    ui->splitter_2->setStretchFactor(1, 1);

	openGLWidget = new GLWidget();

	currentFile = QStandardPaths::locate(QStandardPaths::HomeLocation, QString(),
											  QStandardPaths::LocateDirectory);
	// set current path to file to the home directory - makes browsing files easier

    timer = new QTimer(this);
    timer->start();
	// make a timer for the GL widget

	connect(timer, SIGNAL(timeout()), openGLWidget, SLOT(update()));
	// GL widget updates every tick

    about = new About();

    /** MENU ACTIONS **/

    connect(ui->actionFragmentEditor, SIGNAL(triggered()), ui->fragPlainTextEdit, SLOT(toggle()));
	connect(ui->actionVertexEditor, SIGNAL(triggered()), ui->vertPlainTextEdit, SLOT(toggle()));
	// shows either editor pane when checking their corresponding menu option

    connect(ui->actionAbout, SIGNAL(triggered()), about, SLOT(show()));
	// opens the about and license dialog

    connect(ui->actionExit, SIGNAL(triggered()), about, SLOT(close()));
	// closes the program

    connect(ui->actionRun, SIGNAL(triggered()), this, SLOT(sendStrings()));
	// makes the main window send shader code to the GL widget

	connect(ui->actionReset, SIGNAL(triggered()), openGLWidget, SLOT(reset()));
	// resets the time in the GL widget

	connect(ui->actionBreak, SIGNAL(triggered()), openGLWidget, SLOT(close()));
	// closes the GL widget

	connect(ui->actionOpen, SIGNAL(triggered()), this, SLOT(open()));
	// opens a .glsl file

	connect(ui->actionSave, SIGNAL(triggered()), this, SLOT(save()));
	// saves a .glsl file

	connect(ui->actionImport_texture, SIGNAL(triggered()), this, SLOT(importTexture()));
	// imports a texture

	connect(ui->actionImport_model, SIGNAL(triggered()), this, SLOT(importModel()));
	// imports a model

    /** CONTEXT SPECIFIC **/

    connect(this, SIGNAL(strings(std::string,std::string)),
			openGLWidget, SLOT(compileShader(std::string,std::string)));
	// directs the GL widget to compile the shader code

	connect(this, SIGNAL(pathToTexture(QString)), openGLWidget, SLOT(loadTexture(QString)));
	// sends path to texture file to the GL widget

	connect(this, SIGNAL(pathToModel(QString)), openGLWidget, SLOT(loadModel(QString)));

    /** ERROR OUTPUT **/

	ui->textBrowser->hide();	// don't show the error pane by default
	connect(openGLWidget, SIGNAL(shaderError(QString)), ui->textBrowser, SLOT(setPlainText(QString)));
	// sets text in the error pane if there was an error while compiling the shaders

    connect(ui->textBrowser, SIGNAL(textChanged()), ui->textBrowser, SLOT(show()));
	// shows the error pane when an error occurs

	vertexSyntaxHighlighter = new GLSLSyntax(ui->vertPlainTextEdit->document());
	fragmentSyntaxHighlighter = new GLSLSyntax(ui->fragPlainTextEdit->document());
}

void IDE::open()
{
	openGLWidget->close();
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
}

void IDE::save()
{
	openGLWidget->close();
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
	openGLWidget->show();
	emit strings( ui->vertPlainTextEdit->toPlainText().toStdString(),
				  ui->fragPlainTextEdit->toPlainText().toStdString() );
}

void IDE::importTexture()
{
	openGLWidget->close();
	QString texturePath = QFileDialog::getOpenFileName(this, "Import texture", "",
													   "BMP files (*.bmp);;"
														"GIF files (*.gif);;"
														"JPEG files (*.jpg, *.jpeg);;"
														"PNG files (*.png);;"
														"XBM files (*.xbm);;"
														"XPM files (*.xpm);;"
													   "All files (*.*)");
	emit pathToTexture(texturePath);	// forward the file path to the GL widget
}

void IDE::importModel()
{
	openGLWidget->close();
	QString modelPath = QFileDialog::getOpenFileName(this, "Import model", "",
													   "OBJ files (*.obj);;"
													   "All files (*.*)");
	emit pathToModel(modelPath);	// forward the file path to the GL widget
}

IDE::~IDE()
{
	timer->stop();
	delete vertexSyntaxHighlighter;
	delete fragmentSyntaxHighlighter;
    delete timer;
    delete about;
    delete ui;
}
