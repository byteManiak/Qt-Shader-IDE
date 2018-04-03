#ifndef GLSLSYNTAX_H
#define GLSLSYNTAX_H

#include <QWidget>
#include <QSyntaxHighlighter>
#include <QRegularExpression>
#include <QVector>

class GLSLSyntax : public QSyntaxHighlighter
{
    Q_OBJECT
public:
	explicit GLSLSyntax(QTextDocument *parent = 0);

protected:
	void highlightBlock(const QString&);

private:
	QTextCharFormat keywordFormat;
	QTextCharFormat functionFormat;

	struct Rule
	{
		QRegularExpression regexp;
		QTextCharFormat wordFormat;
	};

	QVector<Rule> keywordRules;
	QVector<Rule> functionRules;
};

#endif // GLSLSYNTAX_H
