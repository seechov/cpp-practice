#include "dispatcher.h"
#include <QDebug>

Dispatcher::Dispatcher(QObject *parent) : QObject(parent)
{
    currentProjectIndex = -1;
}

void Dispatcher::setProjectMenu(QMenu *menu)
{
    projectMenu = menu;
}

void Dispatcher::setCloseCurrentProjectAction(QAction *action)
{
    closeCurrentProjectAction = action;
    closeCurrentProjectAction->setEnabled(false);
}

void Dispatcher::setNoProjectFakeAction(QAction *action)
{
    noProjectOpenedFakeAction = action;
}

void Dispatcher::newProject(QString path)
{
    bool isProjectWasCreated = false;
    if (openedProjects.contains(path)) { // if project already opened
        // switch project to the desired one
        qDebug() << "Switching to the " << path << " project";
    } else {
        // create a new project
        qDebug() << "Creating a new " << path << " project";

        createProjectWidgetAndModel(path);
        openedProjects.append(path);
        createAction();
        isProjectWasCreated = true;
    }

    currentProjectIndex = openedProjects.indexOf(path);
    qDebug() << "Current project is " << openedProjects.at(currentProjectIndex);

    if (isProjectWasCreated) {
        emit projectWasCreated(openedProjects.at(currentProjectIndex));
    } else {
        emit projectWasChanged(openedProjects.at(currentProjectIndex));
    }

    renderProjectMenu();
}

void Dispatcher::openProject(QString path)
{
    bool isProjectWasOpened = false;
    if (openedProjects.contains(path)) { // if project already opened
        // switch project to the desired one
        qDebug() << "Switching to the " << path << " project";
    } else {
        // create a new project
        qDebug() << "Opening a " << path << " project";

        createProjectWidgetAndModel(path);
        openedProjects.append(path);
        createAction();
        isProjectWasOpened = true;
    }

    currentProjectIndex = openedProjects.indexOf(path);
    qDebug() << "Current project is " << openedProjects.at(currentProjectIndex);

    if (isProjectWasOpened) {
        emit projectWasOpened(openedProjects.at(currentProjectIndex));
    } else {
        emit projectWasChanged(openedProjects.at(currentProjectIndex));
    }

    renderProjectMenu();
}

void Dispatcher::closeCurrentProject()
{
    if ((currentProjectIndex < openedProjects.size()) &&
            (currentProjectIndex >= 0)) {
        QString path = openedProjects.at(currentProjectIndex);
        openedProjects.removeOne(path);
        deleteProjectWidgetAndModel(path);
        deleteOneAction();

        qDebug() << "Project " << path << " has been closed.";
        emit projectWasClosed(path);

        if (openedProjects.size() > 0) {
            currentProjectIndex = 0;
            qDebug() << "Current project is " << openedProjects.at(currentProjectIndex);
            emit projectWasChanged(openedProjects.at(currentProjectIndex));
        } else {
            currentProjectIndex = -1;
            qDebug() << "There is no current project";
            emit allProjectsWasClosed();
        }
    }
    renderProjectMenu();
}

ProjectWidget* Dispatcher::getProjectWidget(QString path)
{
    if (projectWidgetMap.contains(path)) {
        return projectWidgetMap[path];
    } else {
        qWarning() << "projectWidgetMap does not contain path " << path << " . Returning nullptr.";
        return nullptr;
    }
}

void Dispatcher::createAction()
{
    QAction *newProjectAction;
    newProjectAction = new QAction(parent());
    connect(newProjectAction, &QAction::triggered, this, &Dispatcher::onProjectAction);
    newProjectAction->setCheckable(true);

    openedProjectsActions.append(newProjectAction);
    projectMenu->addAction(newProjectAction);
}

void Dispatcher::deleteOneAction()
{
    QAction *actionForDelete = openedProjectsActions.last();
    openedProjectsActions.removeLast();

    actionForDelete->disconnect();
    projectMenu->removeAction(actionForDelete);
    actionForDelete->deleteLater();
}

void Dispatcher::renderProjectMenu()
{
    if (openedProjects.size() != openedProjectsActions.size()) {
        qWarning() << "Dispatcher::renderProjectMenu openedProjects.size() != openedProjectsActions.size() "
                   << openedProjects.size() << " != " << openedProjectsActions.size();
    }
    if (openedProjects.size() == openedProjectsActions.size()) {
        for (int i = 0; i < openedProjects.size(); ++i) {
            QAction *projectAction = openedProjectsActions.at(i);
            QString path = openedProjects.at(i);
            if (i < 9) {
                projectAction->setText(tr("&%1 Project %2").arg(QString::number(i + 1), path));
            } else {
                projectAction->setText(tr("%1 Project %2").arg(QString::number(i + 1), path));
            }
            projectAction->setStatusTip(tr("Open project %1").arg(path));
            projectAction->setProperty("path", path);
            if (i == currentProjectIndex) {
                projectAction->setChecked(true);
            } else {
                projectAction->setChecked(false);
            }
            qDebug() << "Render action for project " << path;
        }
    }
    if (currentProjectIndex == -1) {
        closeCurrentProjectAction->setEnabled(false);
        noProjectOpenedFakeAction->setVisible(true);
    } else {
        closeCurrentProjectAction->setEnabled(true);
        noProjectOpenedFakeAction->setVisible(false);
    }
}

void Dispatcher::createProjectWidgetAndModel(QString path)
{
    ProjectWidget *projectWidget = new ProjectWidget();
    projectWidget->setProperty("path", path);
    projectWidgetMap.insert(path, projectWidget);

    ProjectModel *projectModel = new ProjectModel();
    projectModel->setProperty("path", path);
    projectModelMap.insert(path, projectModel);
}

void Dispatcher::deleteProjectWidgetAndModel(QString path)
{
    if (projectWidgetMap.contains(path) && projectModelMap.contains(path)) {
        ProjectWidget *projectWidget = projectWidgetMap[path];
        ProjectModel *projectModel = projectModelMap[path];

        projectWidget->disconnect();
        projectModel->disconnect();

        projectWidget->deleteLater();
        projectModel->deleteLater();
    } else {
        qWarning() << "Dispatcher::deleteProjectWidgetAndModel: path " << path << " is not  in projectWidgetMap or projectModelMap";
    }
}

void Dispatcher::onProjectAction()
{
    QAction* action = (QAction*)sender();
    QString path = action->property("path").toString();

    qDebug() << "One project action. path = " << path;

    currentProjectIndex = openedProjects.indexOf(path);
    qDebug() << "Current project is " << openedProjects.at(currentProjectIndex);

    renderProjectMenu();
    emit projectWasChanged(openedProjects.at(currentProjectIndex));
}


