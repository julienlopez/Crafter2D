#include "dataaccessor.hpp"

#include "playeraccessor.hpp"
#include "buildingaccessor.hpp"
#include "objectaccessor.hpp"
#include "staticObjectaccessor.hpp"

#include <typeinfo>
#include <QDebug>

DataAccessor DataAccessor::m_instance;

DataAccessor::~DataAccessor()
{
    delete playerAccessor;
    delete buildingAccessor;
    delete objectAccessor;
    delete staticObjectAccessor;
}

DataAccessor& DataAccessor::instance() {
    return m_instance;
}

DataAccessor::DataAccessor(): QObject()
{
    playerAccessor = new PlayerAccessor;
    buildingAccessor = new BuildingAccessor;
    objectAccessor = new ObjectAccessor;
    staticObjectAccessor = new StaticObjectAccessor;
}

gPlayer* DataAccessor::getPlayer(quint64 id)
{
    return instance().playerAccessor->get(id);
}

void DataAccessor::save(sWorldElement* element, bool destroy)
{
    instance().m_saveQueue.push_back(toSave(element, destroy));
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
