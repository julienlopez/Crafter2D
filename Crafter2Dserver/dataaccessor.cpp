#include "dataaccessor.hpp"

#include "playeraccessor.hpp"
#include "buildingaccessor.hpp"
#include "objectaccessor.hpp"
#include "staticObjectaccessor.hpp"

#include <QSqlQuery>

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

/*
void DataAccessor::save(gPlayer* player)
{
    qDebug() << "destruction du player " << id();
    QSqlQuery query;
    query.prepare("UPDATE user SET position=:pos WHERE id=:id");
    query.bindValue(":pos", position().toString());
    query.bindValue(":id", id());
    if(!query.exec())
    {
        qDebug() << "impossible d'executer la sauvegarde de sPlayer" << query.lastError().text();
        //SUtils::log() << "impossible d'executer la sauvegarde de sPlayer" + query.lastError().text() + '\n' ;
        return;
    }
    qDebug() << "player sauvegardé";
}*/

void DataAccessor::save(sWorldElement* building, bool destroy)
{
    instance().m_saveQueue.push_back(toSave(building, destroy));
}

void DataAccessor::processSavingQueue()
{
    while(!m_saveQueue.isEmpty())
    {
        toSave s = m_saveQueue.first();
        m_saveQueue.pop_front();
        s.m_object->save();
        if(s.m_destroy) delete s.m_object;
    }
}

DataAccessor::Exception::Exception(const QString& message) throw(): std::exception(), m_message(message)
{}

DataAccessor::Exception::~Exception() throw()
{}

QString DataAccessor::Exception::message() const
{
    return m_message;
}
