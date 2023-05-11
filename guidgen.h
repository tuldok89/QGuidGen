#ifndef GUIDGEN_H
#define GUIDGEN_H

#include <QUuid>
#include <QObject>

class GuidGen : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QUuid Guid READ getGuid WRITE setGuid NOTIFY guidChanged)
public:
    GuidGen();
    const QUuid& getGuid() const;
    void newGuid();
public slots:
    void setGuid(QUuid uuid);
signals:
    void guidChanged(const QUuid& uuid);
private:
    QUuid _uuid;
};

#endif // GUIDGEN_H
