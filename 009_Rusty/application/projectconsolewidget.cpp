#include "projectconsolewidget.h"

ProjectConsoleWidget::ProjectConsoleWidget(QWidget *parent) : QWidget(parent)
{
    console = new ConsoleWidget;

    mainLayout = new QVBoxLayout;
    mainLayout->addWidget(console);
    setLayout(mainLayout);
}
