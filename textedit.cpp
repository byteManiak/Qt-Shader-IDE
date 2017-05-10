#include "textedit.h"

TextEdit::TextEdit(QWidget *parent) : QPlainTextEdit(parent)
{
    QFontMetrics f(font());
    setTabStopWidth(10*f.width(' '));
}

void TextEdit::toggle()
{
    if(isHidden()) show();
    else hide();
}
