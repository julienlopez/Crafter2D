#include "dataaccessor.hpp"
#include "playeraccessor.hpp"
#include "buildingaccessor.hpp"
#include "objectaccessor.hpp"
#include "staticObjectaccessor.hpp"

#include <typeinfo>
#include <QDebug>

DataAccessor::~DataAccessor()
{
    delete playerAccessor;
    delete buildingAccessor;
    delete objectAccessor;
    delete staticObjectAccessor;
}

DataAccessor::DataAccessor(): QObject()
{
    playerAccessor = new PlayerAccessor;
    buildingAccessor = new BuildingAccessor;
    objectAccessor = new ObjectAccessor;
    staticObjectAccessor = new StaticObjectAccessor;
}

WorldElement* DataAccessor::getWorldElement(quint64 code, quint64 id)
{
    switch(code){
    case gPlayer::s_code:
        return getPlayer(id);
    case gBuilding::s_code:
        return getBuilding(id);
    case gObject::s_code:
        return getObject(id);
    case gStaticObject::s_code:
        return  getStaticObject(id);
    }
    return 0;
}

sPlayer* DataAccessor::getPlayer(quint64 id)
{
    return instance().playerAccessor->get(id);
}

gBuilding* DataAccessor::getBuilding(quint64 id)
{
    return instance().buildingAccessor->get(id);
}

gObject* DataAccessor::getObject(quint64 id)
{
    return instance().objectAccessor->get(id);
}

gStaticObject* DataAccessor::getStaticObject(quint64 id)
{
    return instance().staticObjectAccessor->get(id);
}

QList<quint64> DataAccessor::getNearbyStaticObjects(const Position& pos, double distance)
{
    StaticObjectAccessor* acc = instance().staticObjectAccessor;
    Q_ASSERT(acc);
    return acc->getIdByPosition(pos, distance);
}

void DataAccessor::save(sWorldElement* element, bool destroy)
{
    instance().m_saveQueue.push_back(toSave(element, destroy));
}

void DataAccessor::clearAll()
{
    qDebug() << "DataAccessor::clearAll\n";
    playerAccessor->clear();
    buildingAccessor->clear();
    objectAccessor->clear();
    staticObjectAccessor->clear();
}

void DataAccessor::processSavingQueue()
{
    while(!m_saveQueue.isEmpty())
    {
        toSave s = m_saveQueue.first();
        m_saveQueue.pop_front();
        qDebug() << "saving " << typeid(*s.m_object).name() << " avec l'id ";
        s.m_object->save();
        if(s.m_destroy) delete s.m_object;
    }
}

void DataAccessor::saveSlot(sWorldElement* element, bool destroy)
{
    m_saveQueue.push_back(toSave(element, destroy));
}

DataAccessor::Exception::Exception(const QString& message) throw(): std::exception(), m_message(message)
{}

DataAccessor::Exception::~Exception() throw()
{}

QString DataAccessor::Exception::message() const
{
    return m_message;
}
