#ifndef LICENSEWIDGET_H
#define LICENSEWIDGET_H

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

class LicenseWidget : public QDialog
{
    Q_OBJECT
public:
    explicit LicenseWidget(QWidget *parent = nullptr);
    ~LicenseWidget();

signals:
    void licenseAttempt(QString email, QString license);

private slots:
    void makeLicenseAttempt();

private:
    QVBoxLayout *mainLayout;
    QHBoxLayout *emailLayout;
    QHBoxLayout *licenseLayout;
    QHBoxLayout *buttonsLayout;

    QLabel *emailLabel;
    QLineEdit *emailLineEdit;

    QLabel *licenseLabel;
    QLineEdit *licenseLineEdit;

    QPushButton *applyLicenseButton;
    QPushButton *cancelButton;
};

#endif // LICENSEWIDGET_H
