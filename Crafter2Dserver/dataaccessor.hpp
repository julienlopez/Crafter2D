#ifndef DATAACCESSOR_HPP
#define DATAACCESSOR_HPP

#include <QObject>

#include "playeraccessor.hpp"
#include "buildingaccessor.hpp"
#include "objectaccessor.hpp"
#include "staticObjectaccessor.hpp"

class DataAccessor : public QObject
{
    Q_OBJECT
public:
    static DataAccessor& instance();

    static Player* getPlayer(quint64 id);
    static Building* getBuilding(quint64 id);
    static Object* getObject(quint64 id);
    static StaticObject* getStaticObject(quint64 id);

private:
    static DataAccessor m_instance;

    DataAccessor();

    PlayerAccessor playerAccessor;
    BuildingAccessor buildingAccessor;
    ObjectAccessor objectAccessor;
    StaticObjectAccessor staticObjectAccessor;

signals:

public slots:

};

#endif // DATAACCESSOR_HPP
