#include "dataaccessor.hpp"

#include "playeraccessor.hpp"
#include "buildingaccessor.hpp"
#include "objectaccessor.hpp"
#include "staticObjectaccessor.hpp"

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

DataAccessor::Exception::Exception(const QString& message) throw(): std::exception(), m_message(message)
{}

DataAccessor::Exception::~Exception() throw()
{}

QString DataAccessor::Exception::message() const
{
    return m_message;
}
