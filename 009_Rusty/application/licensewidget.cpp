#include "licensewidget.h"

LicenseWidget::LicenseWidget(QWidget *parent) : QDialog(parent, Qt::Popup | Qt::Dialog)
{
    setWindowTitle(tr("Enter purchased license"));
    setMinimumWidth(400);

    mainLayout = new QVBoxLayout();
    emailLayout = new QHBoxLayout();
    licenseLayout = new QHBoxLayout();
    buttonsLayout = new QHBoxLayout();

    emailLabel = new QLabel(tr("E-mail:"), this);
    emailLineEdit = new QLineEdit(tr("name@example.com"), this);

    licenseLabel = new QLabel(tr("License key"), this);
    licenseLineEdit = new QLineEdit(tr("aabbccddeeffgghhkkllmmnnoopp"), this);

    applyLicenseButton = new QPushButton(tr("&Ok"), this);
    applyLicenseButton->setShortcut(QKeySequence(Qt::Key_Enter | Qt::Key_Return));
    connect(applyLicenseButton, &QPushButton::clicked, this, &LicenseWidget::makeLicenseAttempt);

    cancelButton = new QPushButton(tr("&Cancel"), this);
    cancelButton->setShortcut(QKeySequence(Qt::Key_Escape));
    connect(cancelButton, &QPushButton::clicked, this, &LicenseWidget::close);

    emailLayout->addWidget(emailLabel);
    emailLayout->addWidget(emailLineEdit);
    mainLayout->addLayout(emailLayout);

    licenseLayout->addWidget(licenseLabel);
    licenseLayout->addWidget(licenseLineEdit);
    mainLayout->addLayout(licenseLayout);

    buttonsLayout->addStretch();
    buttonsLayout->addWidget(applyLicenseButton);
    buttonsLayout->addWidget(cancelButton);
    mainLayout->addLayout(buttonsLayout);

    setLayout(mainLayout);
}

LicenseWidget::~LicenseWidget(){
    mainLayout->deleteLater();
    emailLayout->deleteLater();
    licenseLayout->deleteLater();
    buttonsLayout->deleteLater();
}

void LicenseWidget::makeLicenseAttempt()
{
    emit licenseAttempt(emailLineEdit->text(), licenseLineEdit->text());
}
