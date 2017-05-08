#include "textedit.h"

TextEdit::TextEdit(QWidget *parent) : QTextEdit(parent)
{
    QFontMetrics f(this->font());
    setTabStopWidth(f.width("    "));
}

void TextEdit::toggle()
{
    if(isHidden()) show();
    else hide();
}
