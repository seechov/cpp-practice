#ifndef PROJECTCONSOLEWIDGET_H
#define PROJECTCONSOLEWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include "consolewidget.h"

class ProjectConsoleWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ProjectConsoleWidget(QWidget *parent = nullptr);

signals:

private:
    QVBoxLayout *mainLayout;
    ConsoleWidget *console;
};

#endif // PROJECTCONSOLEWIDGET_H
