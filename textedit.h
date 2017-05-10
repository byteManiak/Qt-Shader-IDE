#ifndef TEXTEDIT_H
#define TEXTEDIT_H

#include <QWidget>
#include <QPlainTextEdit>
#include <QSyntaxHighlighter>

class TextEdit : public QPlainTextEdit
{
    Q_OBJECT
public:
    explicit TextEdit(QWidget *parent = 0);

public slots:
    void toggle();
};

#endif // TEXTEDIT_H
