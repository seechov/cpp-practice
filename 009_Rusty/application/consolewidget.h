#ifndef CONSOLEWIDGET_H
#define CONSOLEWIDGET_H

#include <QTextEdit>

class ConsoleWidget : public QTextEdit
{
    Q_OBJECT
public:
    explicit ConsoleWidget(QWidget *parent = nullptr);

protected:
    void keyPressEvent(QKeyEvent *event);
};

#endif // CONSOLEWIDGET_H
