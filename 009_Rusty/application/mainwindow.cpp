#include <QSettings>
#include <QMessageBox>
#include <QMenuBar>
#include <QDesktopServices>
#include <QUrl>
#include <QApplication>
#include <QCryptographicHash>
#include <QScreen>
#include <QDebug>
#include "mainwindow.h"
#include "projectmodel.h"
#include "projectwidget.h"

const QString MainWindow::organizationDomain("spacedigits.com");
const QString MainWindow::organizationName("Space Digits");
const QString MainWindow::applicationName("Rusty");
const QString MainWindow::licenseSalt("t*+tG6:g*!.5~KTGD3Ew69");
const int     MainWindow::maxMultilineLicenseNumber(1000);

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), licenseWidget(new LicenseWidget(this))
{
    qSetMessagePattern("%{function}(line:%{line}) %{message}");

    setApplicationCredentials();
    readSettings();
    createActions();
    createMenus();

    createNewProjectFileDialog();
    createOpenProjectFileDialog();

    performSignalWiring();

    checkLicense();
}

MainWindow::~MainWindow()
{
    licenseWidget->deleteLater();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    QSettings settings(qApp->organizationName(), qApp->applicationName());
    settings.setValue("MainWindow/geometry", saveGeometry());
    settings.setValue("MainWindow/windowState", saveState());

    QMainWindow::closeEvent(event);
}

void MainWindow::setApplicationCredentials()
{
    qApp->setOrganizationDomain(organizationDomain);
    qApp->setOrganizationName(organizationName);
    qApp->setApplicationName(applicationName);
}

void MainWindow::readSettings()
{
    QSettings settings(qApp->organizationName(), qApp->applicationName());
    if (settings.contains("MainWindow/geometry") && (settings.contains("MainWindow/windowState"))) {
        restoreGeometry(settings.value("MainWindow/geometry").toByteArray());
        restoreState(settings.value("MainWindow/windowState").toByteArray());
    } else {
        QScreen* screen = QGuiApplication::primaryScreen();
        resize(screen->availableGeometry().size() * 0.7);
        //resize(QDesktopWidget().availableGeometry(this).size() * 0.7);
    }
}

void MainWindow::createActions()
{
    newProjectAction = new QAction(tr("&New Project..."), this);
    newProjectAction->setShortcuts(QKeySequence::New);
    newProjectAction->setStatusTip(tr("Create new project."));
    connect(newProjectAction, &QAction::triggered, this, &MainWindow::createNewProject);

    openProjectAction = new QAction(tr("&Open Project..."), this);
    openProjectAction->setShortcuts(QKeySequence::Open);
    openProjectAction->setStatusTip(tr("Open existing project."));
    connect(openProjectAction, &QAction::triggered, this, &MainWindow::openProject);

    closeProjectAction = new QAction(tr("&Close current project"), this);
    closeProjectAction->setShortcuts(QKeySequence::Close);
    closeProjectAction->setStatusTip(tr("Close current project."));
    connect(closeProjectAction, &QAction::triggered, this, &MainWindow::closeCurrentProject);

    quitAction = new QAction(tr("&Quit"), this);
    quitAction->setShortcuts(QKeySequence::Quit);
    quitAction->setStatusTip(tr("Quit Rutsy."));
    connect(quitAction, &QAction::triggered, this, &MainWindow::quit);

    noProjectOpenedFakeAction = new QAction(tr("No project opened"), this);
    noProjectOpenedFakeAction->setStatusTip(tr("No project opened."));
    noProjectOpenedFakeAction->setDisabled(true);

    aboutAction = new QAction(tr("&About"), this);
    aboutAction->setStatusTip(tr("About Rutsy."));
    connect(aboutAction, &QAction::triggered, this, &MainWindow::about);

    purchaseLicenseAction = new QAction(tr("&Purchase License"), this);
    purchaseLicenseAction->setStatusTip(tr("Purchase Rusty license on the web."));
    connect(purchaseLicenseAction, &QAction::triggered, this, &MainWindow::purchaseLicense);

    enterLicenseAction = new QAction(tr("&Enter License"), this);
    enterLicenseAction->setStatusTip(tr("Enter purchased license."));
    connect(enterLicenseAction, &QAction::triggered, this, &MainWindow::enterLicense);
}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newProjectAction);
    fileMenu->addAction(openProjectAction);
    fileMenu->addAction(closeProjectAction);
    fileMenu->addSeparator();
    fileMenu->addAction(quitAction);

    projectMenu = menuBar()->addMenu(tr("&Project"));
    projectMenu->addAction(noProjectOpenedFakeAction);

    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(purchaseLicenseAction);
    helpMenu->addAction(enterLicenseAction);
    helpMenu->addAction(aboutAction);
}

bool MainWindow::isValidIndividualLicense(QString email, QString license)
{
    license = license.trimmed().toLower();
    email = email.trimmed().toLower();

    QString licenseInitialString = licenseSalt + email;

    QString desiredLicense;
    desiredLicense = QCryptographicHash::hash(licenseInitialString.toUtf8(), QCryptographicHash::Md5).toHex().toLower();
    // qDebug() << "Desired license is " << desiredLicense;

    if (desiredLicense == license) {
        return true;
    } else {
        return false;
    }
}

QPair<bool, int> MainWindow::isValidMultiLicense(QString email, QString license)
{
    QString licenseInitialString, desiredLicense;
    license = license.trimmed().toLower();
    email = email.trimmed().toLower();

    for (int i = 0; i < maxMultilineLicenseNumber; ++i) {
        licenseInitialString = licenseSalt + QString::number(i) + email;
        desiredLicense = QCryptographicHash::hash(licenseInitialString.toUtf8(), QCryptographicHash::Md5).toHex().toLower();
        // qDebug() << "Desired license is " << desiredLicense;
        if (desiredLicense == license) {
            return QPair<bool, int>(true, i);
        }
    }
    return QPair<bool, int>(false, 0);
}

void MainWindow::saveLicense(QString email, QString license)
{
    QSettings settings(qApp->organizationName(), qApp->applicationName());
    settings.setValue("license/email", email.trimmed().toLower());
    settings.setValue("license/key", license.trimmed().toLower());
}

void MainWindow::createNewProjectFileDialog()
{
    newProjectFileDialog = new QFileDialog(this, tr("Choose empty directory for the new project"));
    newProjectFileDialog->setFileMode(QFileDialog::DirectoryOnly);
    newProjectFileDialog->setOption(QFileDialog::ShowDirsOnly, false);
    newProjectFileDialog->setModal(true);
    connect(newProjectFileDialog, &QFileDialog::accepted, this, &MainWindow::onNewProjectDialogAccept);
    connect(newProjectFileDialog, &QFileDialog::finished, this, &MainWindow::grabFocusAfterDialogEnding);
}

void MainWindow::createOpenProjectFileDialog()
{
    openProjectFileDialog = new QFileDialog(this, tr("Choose empty directory for the new project"));
    openProjectFileDialog->setFileMode(QFileDialog::DirectoryOnly);
    openProjectFileDialog->setOption(QFileDialog::ShowDirsOnly, false);
    openProjectFileDialog->setModal(true);
    connect(openProjectFileDialog, &QFileDialog::accepted, this, &MainWindow::onOpenProjectDialogAccept);
    connect(openProjectFileDialog, &QFileDialog::finished, this, &MainWindow::grabFocusAfterDialogEnding);
}

void MainWindow::performSignalWiring()
{
    dispatcher.setParent(this);
    dispatcher.setProjectMenu(projectMenu);
    dispatcher.setCloseCurrentProjectAction(closeProjectAction);
    dispatcher.setNoProjectFakeAction(noProjectOpenedFakeAction);

    connect(licenseWidget, &LicenseWidget::licenseAttempt, this, &MainWindow::onLicenseAttempt);

    connect(&dispatcher, &Dispatcher::projectWasCreated, this, &MainWindow::onProjectWasCreated);
    connect(&dispatcher, &Dispatcher::projectWasOpened, this, &MainWindow::onProjectWasOpened);
    connect(&dispatcher, &Dispatcher::projectWasChanged, this, &MainWindow::onProjectWasChanged);
    connect(&dispatcher, &Dispatcher::allProjectsWasClosed, this, &MainWindow::onAllProjectsWasClosed);
}

void MainWindow::checkLicense()
{
    QSettings settings(qApp->organizationName(), qApp->applicationName());
    QString email = settings.value("license/email").toString();
    QString license = settings.value("license/key").toString();

    // qDebug() << "email = " << email;
    // qDebug() << "license = " << license;

    if (isValidIndividualLicense(email, license)) {
        licensePresence = true;
        setWindowTitle(tr("Rusty — registered to %1").arg(email));
    } else {
        QPair<bool, int> multiLicenseResult = isValidMultiLicense(email, license);
        if (multiLicenseResult.first) {
            licensePresence = true;
            setWindowTitle(tr("Rusty — registered as multilicened product to %1. License #%2.")
                           .arg(email, QString::number(multiLicenseResult.second + 1)));
        } else {
            licensePresence = false;
            setWindowTitle(tr("Rusty — unregistered"));
        }
    }
}

void MainWindow::quit()
{
    close();
}

void MainWindow::about()
{
    QMessageBox::about(this, tr("About Rusty"),
            tr("This is the version 0.1 of Rusty. "
               "The <b>Menu</b> example shows how to create "
               "menu-bar menus and context menus."));
}

void MainWindow::purchaseLicense()
{
    QDesktopServices::openUrl(QUrl("https://spacedigits.com/buy-rusty/", QUrl::TolerantMode));
}

void MainWindow::enterLicense()
{
    licenseWidget->open();
    licenseWidget->activateWindow();
    // Possibly I will need this uncommented for the other OS
    //licenseWidget->raise();
    //licenseWidget->setFocus();
}

void MainWindow::onLicenseAttempt(QString email, QString license)
{
    if (isValidIndividualLicense(email, license)) {
        licenseWidget->close();
        saveLicense(email, license);
        checkLicense();
        //QMessageBox::about(this, tr("Valid license"),
        //        QString(tr("Valid license. Email %1. License %2.")).arg(email, license));
    } else {
        QPair<bool, int> multiLicenseResult = isValidMultiLicense(email, license);
        if (multiLicenseResult.first) {
            licenseWidget->close();
            saveLicense(email, license);
            checkLicense();
            //QMessageBox::about(this, tr("Valid license"),
            //        QString(tr("Email %1. License %2. Number of multilicense is %3"))
            //                   .arg(email, license, QString::number(multiLicenseResult.second)));

        } else {
            QMessageBox::about(this, tr("Non-valid license"),
                    QString(tr("Sorry, your license key is not valid. Email: %1. License: %2.")).arg(email, license));
        }
    }
}

void MainWindow::createNewProject()
{
    // newProjectFileDialog->open();
    openProjectFileDialog->show();
}

void MainWindow::openProject()
{
    // openProjectFileDialog->open();
    openProjectFileDialog->show();
}

void MainWindow::closeCurrentProject()
{
    dispatcher.closeCurrentProject();
}

void MainWindow::onNewProjectDialogAccept()
{
    QString path = newProjectFileDialog->directory().path();
    dispatcher.newProject(path);
}

void MainWindow::onOpenProjectDialogAccept()
{
    QString path = openProjectFileDialog->directory().path();
    dispatcher.openProject(path);
}

void MainWindow::grabFocusAfterDialogEnding(int i)
{
    activateWindow();

    // here is some code to skip warning about unused i variable.
    // This code does nothing.
    if (i == QDialog::Accepted || i == QDialog::Rejected) {
        i = i + 1 - 1;
    }
}

void MainWindow::onProjectWasCreated(QString path)
{
    qDebug() << "Project is " << path;
    currentProjectWidget = dispatcher.getProjectWidget(path);
    currentProjectWidget->setProjectName(path);
    takeCentralWidget();
    setCentralWidget(currentProjectWidget);
}

void MainWindow::onProjectWasOpened(QString path)
{
    qDebug() << "Project is " << path;
    currentProjectWidget = dispatcher.getProjectWidget(path);
    currentProjectWidget->setProjectName(path);
    takeCentralWidget();
    setCentralWidget(currentProjectWidget);
}

void MainWindow::onProjectWasChanged(QString path)
{
    qDebug() << "Project is " << path;
    currentProjectWidget = dispatcher.getProjectWidget(path);
    takeCentralWidget();
    setCentralWidget(currentProjectWidget);
}

void MainWindow::onAllProjectsWasClosed()
{
    qDebug() << "Executing.";
    takeCentralWidget();
    setCentralWidget(nullptr);
}
