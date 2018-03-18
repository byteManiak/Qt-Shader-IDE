#include "textedit.h"

TextEdit::TextEdit(QWidget *parent) : QPlainTextEdit(parent)
{
    QFontMetrics f(font());
    setTabStopDistance(4*f.width('a'));
}

void TextEdit::toggle()
{
    if(isHidden()) show();
    else hide();
}
