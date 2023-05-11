#include "guidgen.h"

GuidGen::GuidGen()
{

}

const QUuid& GuidGen::getGuid() const
{
    return _uuid;
}

void GuidGen::newGuid()
{
    setGuid(QUuid::createUuid());
}

void GuidGen::setGuid(QUuid uuid)
{
    if (_uuid != uuid)
    {
        _uuid = uuid;
        emit guidChanged(uuid);
    }
}
