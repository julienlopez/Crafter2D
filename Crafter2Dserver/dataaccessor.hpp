#ifndef DATAACCESSOR_HPP
#define DATAACCESSOR_HPP

#include <QObject>

class gPlayer;
class gBuilding;
class gObject;
class gStaticObject;
class PlayerAccessor;
class BuildingAccessor;
class ObjectAccessor;
class StaticObjectAccessor;

class DataAccessor : public QObject
{
    Q_OBJECT
public:
    ~DataAccessor();
    static DataAccessor& instance();

    static gPlayer* getPlayer(quint64 id);
    static gBuilding* getBuilding(quint64 id);
    static gObject* getObject(quint64 id);
    static gStaticObject* getStaticObject(quint64 id);

private:
    static DataAccessor m_instance;

    DataAccessor();

    PlayerAccessor* playerAccessor;
    BuildingAccessor* buildingAccessor;
    ObjectAccessor* objectAccessor;
    StaticObjectAccessor* staticObjectAccessor;

signals:

public slots:

public:
    class Exception : public std::exception
    {
    public:
        Exception(const QString& message) throw();
        virtual ~Exception() throw();

        QString message() const;

    protected:
        QString m_message;
    };

};

#endif // DATAACCESSOR_HPP
