#include "projectwidget.h"
#include <QDebug>
ProjectWidget::ProjectWidget(QWidget *parent) : QWidget(parent)
{
    tabWidget = new QTabWidget;

    mainLayout = new QVBoxLayout;
    mainLayout->addWidget(tabWidget);
    setLayout(mainLayout);

    projectInfoWidget = new ProjectInfoWidget;
    projectConsoleWidget = new ProjectConsoleWidget;

    tabWidget->addTab(projectInfoWidget, tr("Info"));
    tabWidget->addTab(projectConsoleWidget, tr("Console"));
}

ProjectWidget::~ProjectWidget()
{
    qDebug() << "Destruction of " << this->property("path");
}

void ProjectWidget::setProjectName(QString name)
{
    projectInfoWidget->setProjectName(name);
}
