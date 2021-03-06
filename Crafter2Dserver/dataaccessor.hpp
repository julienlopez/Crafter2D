#ifndef DATAACCESSOR_HPP
#define DATAACCESSOR_HPP

#include <Utils/Singleton>

#include <QObject>
#include <QQueue>

class Position;
class sWorldElement;
class WorldElement;
class sPlayer;
class gPlayer;
class gBuilding;
class gObject;
class gStaticObject;
class PlayerAccessor;
class BuildingAccessor;
class ObjectAccessor;
class StaticObjectAccessor;
class QTimer;

class DataAccessor : public QObject, public Utils::Singleton<DataAccessor>
{
    Q_OBJECT

    friend class Utils::Singleton<DataAccessor>;
public:
    ~DataAccessor();

    static WorldElement* getWorldElement(quint64 code, quint64 id);
    static sPlayer* getPlayer(quint64 id);
    static gBuilding* getBuilding(quint64 id);
    static gObject* getObject(quint64 id);
    static gStaticObject* getStaticObject(quint64 id);

    static QList<quint64> getNearbyStaticObjects(const Position& pos, double distance);

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
