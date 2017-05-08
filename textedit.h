#ifndef TEXTEDIT_H
#define TEXTEDIT_H

#include <QWidget>
#include <QTextEdit>

class TextEdit : public QTextEdit
{
    Q_OBJECT
public:
    explicit TextEdit(QWidget *parent = 0);

public slots:
    void toggle();
};

#endif // TEXTEDIT_H
