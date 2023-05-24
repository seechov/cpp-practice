#ifndef PROJECTINFOWIDGET_H
#define PROJECTINFOWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>

class ProjectInfoWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ProjectInfoWidget(QWidget *parent = nullptr);
    void setProjectName(QString name);

signals:

private:
    QVBoxLayout *mainLayout;
    QLabel *projectName;
};

#endif // PROJECTINFOWIDGET_H
