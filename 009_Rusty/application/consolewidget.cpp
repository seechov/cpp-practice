#include <QWidget>
#include <QDebug>
#include "consolewidget.h"

ConsoleWidget::ConsoleWidget(QWidget *parent) : QTextEdit(parent) {

}

void ConsoleWidget::keyPressEvent(QKeyEvent *event)
{
//    qDebug() << "this->document()->blockCount() = " << this->document()->blockCount();
//    qDebug() << "this->textCursor().blockNumber() = " << this->textCursor().blockNumber();
    if ((document()->blockCount() - 1) != textCursor().blockNumber()) {
        moveCursor(QTextCursor::End);
    }

    QTextEdit::keyPressEvent(event);

    if ((document()->blockCount() - 1) != textCursor().blockNumber()) {
        moveCursor(QTextCursor::End);
    }
}
