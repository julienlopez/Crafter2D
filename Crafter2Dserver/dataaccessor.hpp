#ifndef DATAACCESSOR_HPP
#define DATAACCESSOR_HPP

#include <QObject>
#include <QQueue>

class sWorldElement;
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

    static void save(sWorldElement* element, bool destroy = false);

private:
    struct toSave {
        toSave(sWorldElement* object, bool destroy)
        {
            m_object = object;
            m_destroy = destroy;
        }

        sWorldElement* m_object;
        bool m_destroy;
    };

    static DataAccessor m_instance;
    QQueue<toSave> m_saveQueue;

    DataAccessor();

    PlayerAccessor* playerAccessor;
    BuildingAccessor* buildingAccessor;
    ObjectAccessor* objectAccessor;
    StaticObjectAccessor* staticObjectAccessor;

signals:

public slots:
    void processSavingQueue();

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
