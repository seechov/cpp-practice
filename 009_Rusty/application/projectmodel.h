#ifndef PROJECTMODEL_H
#define PROJECTMODEL_H

#include <QObject>

class ProjectModel : public QObject
{
    Q_OBJECT
public:
    explicit ProjectModel(QObject *parent = nullptr);

signals:

};

#endif // PROJECTMODEL_H
