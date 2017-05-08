#include "textedit.h"

TextEdit::TextEdit(QWidget *parent) : QTextEdit(parent)
{

}

void TextEdit::toggle()
{
    if(isHidden()) show();
    else hide();
}
