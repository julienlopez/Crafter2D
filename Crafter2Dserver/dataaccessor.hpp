#ifndef DATAACCESSOR_HPP
#define DATAACCESSOR_HPP

#include <QObject>
#include <QQueue>

class sWorldElement;
class WorldElement;
class gPlayer;
class gBuilding;
class gObject;
class gStaticObject;
class PlayerAccessor;
class BuildingAccessor;
class ObjectAccessor;
class StaticObjectAccessor;
class QTimer;

class DataAccessor : public QObject
{
    Q_OBJECT
public:
    ~DataAccessor();
    static DataAccessor& instance();

    static WorldElement* getWorldElement(quint64 code, quint64 id);
    static gPlayer* getPlayer(quint64 id);
    static gBuilding* getBuilding(quint64 id);
    static gObject* getObject(quint64 id);
    static gStaticObject* getStaticObject(quint64 id);

    static void save(sWorldElement* element, bool destroy = false);
    void clearAll();

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

    PlayerAccessor* playerAccessor;
    BuildingAccessor* buildingAccessor;
    ObjectAccessor* objectAccessor;
    StaticObjectAccessor* staticObjectAccessor;

    DataAccessor();

signals:

public slots:
    void processSavingQueue();
    void saveSlot(sWorldElement* element, bool destroy = false);

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
