#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAction>
#include <QFileDialog>

#include "licensewidget.h"
#include "dispatcher.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void applyLicense(QString email, QString license);

signals:

protected:
    void closeEvent(QCloseEvent *event) override;
private:
    void setApplicationCredentials();
    void readSettings();
    void createActions();
    void createMenus();
    bool isValidIndividualLicense(QString email, QString license);
    QPair<bool, int> isValidMultiLicense(QString email, QString license);
    void saveLicense(QString email, QString license);
    void createNewProjectFileDialog();
    void createOpenProjectFileDialog();
    void performSignalWiring();
    void checkLicense();
    static const QString organizationDomain;
    static const QString organizationName;
    static const QString applicationName;
    static const int maxMultilineLicenseNumber;
    static const QString licenseSalt;
    bool licensePresence;

    LicenseWidget *licenseWidget;

    QMenu *fileMenu;
    QMenu *projectMenu;
    QMenu *helpMenu;

    QAction *newProjectAction;
    QAction *openProjectAction;
    QAction *closeProjectAction;
    QAction *noProjectOpenedFakeAction;
    QAction *quitAction;
    QAction *aboutAction;
    QAction *purchaseLicenseAction;
    QAction *enterLicenseAction;

    QFileDialog *newProjectFileDialog;
    QFileDialog *openProjectFileDialog;

    Dispatcher dispatcher;
    ProjectWidget *currentProjectWidget;

private slots:
    void quit();
    void about();
    void purchaseLicense();
    void enterLicense();
    void onLicenseAttempt(QString email, QString license);
    void createNewProject();
    void openProject();
    void closeCurrentProject();
    void onNewProjectDialogAccept();
    void onOpenProjectDialogAccept();
    void grabFocusAfterDialogEnding(int i);
    void onProjectWasCreated(QString path);
    void onProjectWasOpened(QString path);
    void onProjectWasChanged(QString path);
    void onAllProjectsWasClosed();
};
#endif // MAINWINDOW_H
