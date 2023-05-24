#include "projectinfowidget.h"

ProjectInfoWidget::ProjectInfoWidget(QWidget *parent) : QWidget(parent)
{
    mainLayout = new QVBoxLayout;
    projectName = new QLabel;
    mainLayout->addWidget(projectName);

    setLayout(mainLayout);
}

void ProjectInfoWidget::setProjectName(QString name)
{
    projectName->setText(name);
}
