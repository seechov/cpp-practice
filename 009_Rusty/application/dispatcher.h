#ifndef DISPATCHER_H
#define DISPATCHER_H

#include <QObject>
#include <QMenu>
#include <QAction>
#include <QMap>
#include "projectmodel.h"
#include "projectwidget.h"

class Dispatcher : public QObject
{
    Q_OBJECT
public:
    explicit Dispatcher(QObject *parent = nullptr);
    void setProjectMenu(QMenu *menu);
    void setCloseCurrentProjectAction(QAction *action);
    void setNoProjectFakeAction(QAction *action);
    void newProject(QString path);
    void openProject(QString path);
    void closeCurrentProject();
    ProjectWidget* getProjectWidget(QString path);

signals:
    void projectWasChanged(QString path);
    void projectWasCreated(QString path);
    void projectWasOpened(QString path);
    void projectWasClosed(QString path);
    void allProjectsWasClosed();

private:
    QMenu *projectMenu;
    QAction *closeCurrentProjectAction;
    QAction *noProjectOpenedFakeAction;

    QList<QAction*> openedProjectsActions;
    void createAction();
    void deleteOneAction();
    void renderProjectMenu();

    QStringList openedProjects;
    int currentProjectIndex;

    ProjectWidget *currentProjectWidget;
    ProjectModel *currentProjectModel;
    QMap<QString, ProjectWidget*> projectWidgetMap;
    QMap<QString, ProjectModel*> projectModelMap;
    void createProjectWidgetAndModel(QString path);
    void deleteProjectWidgetAndModel(QString path);

private slots:
    void onProjectAction();
//    void updateLastOpenedProjectIndexList(int previouslyUsedProjectIndex);
//    int popPreviousOpenedProjectIndexList();
};

#endif // DISPATCHER_H
