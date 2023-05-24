#ifndef PROJECTWIDGET_H
#define PROJECTWIDGET_H

#include <QWidget>
#include <QTabWidget>
#include <QVBoxLayout>
#include "projectinfowidget.h"
#include "projectconsolewidget.h"

class ProjectWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ProjectWidget(QWidget *parent = nullptr);
    ~ProjectWidget();
    void setProjectName(QString text);

signals:

private:
    QVBoxLayout *mainLayout;

    QTabWidget *tabWidget;

    ProjectInfoWidget *projectInfoWidget;
    ProjectConsoleWidget *projectConsoleWidget;

};

#endif // PROJECTWIDGET_H
