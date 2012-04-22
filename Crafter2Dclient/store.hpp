#ifndef STORE_HPP
#define STORE_HPP

#include <Message/Message>
#include <Position>
#include <Utils/Singleton>

#include <QMap>

class WorldElement;
class gPlayer;
class cPlayer;
class gBuilding;
class gObject;
class gStaticObject;
class cStaticObject;
class cWorldElement;

/**
  * \brief Classe stoquant les WorldElement utilisés par le client.
  *
  * Conteneur global contenant toutes les données serveurs dont le client a besoin.
  * Demande automatiquement les informations nécessaires si besoin est.
  */
class Store : public QObject, public Utils::Singleton<Store>
{
    Q_OBJECT
    friend class Utils::Singleton<Store>;

public:
    typedef cPlayer* type_player;
    typedef gBuilding* type_building;
    typedef gObject* type_object;
    typedef cStaticObject* type_staticObject;

    static void updatePosition(quint64 code, quint64 id, const Position &pos);
    static void updatePositionPlayer(quint64 id, const Position &pos);
    static void updatePositionBuilding(quint64 id, const Position &pos);
    static void updatePositionObject(quint64 id, const Position &pos);
    static void updatePositionStaticObject(quint64 id, const Position &pos);

    static void setInformation(WorldElement* el);
    static void setInformationPlayer(gPlayer* p);
    static void setInformationBuilding(gBuilding* g);
    static void setInformationObject(gObject* o);
    static void setInformationStaticObject(gStaticObject* s);

    static WorldElement* get(quint64 code, quint64 id);
    static type_player getPlayer(quint64 id);
    static type_building getBuilding(quint64 id);
    static type_object getObjetcs(quint64 id);
    static type_staticObject getStaticObjects(quint64 id);

private:
    Store();

    QMap<quint64, type_player> m_players;
    QMap<quint64, type_building> m_building;
    QMap<quint64, type_object> m_objetcs;
    QMap<quint64, type_staticObject> m_staticobjects;

    void emitMessage(const Message::Message& message);

signals:
    void sendMessage(const Message::Message& message);
    void newElement(cWorldElement*);
};

#endif // STORE_HPP
