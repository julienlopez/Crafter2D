#ifndef STORE_HPP
#define STORE_HPP

#include <Message/Message>
#include <Position>

#include <QMap>

class WorldElement;
class gPlayer;
class cPlayer;
class gBuilding;
class gObject;
class gStaticObject;
class cWorldElement;

/**
  * \brief Classe stoquant les WorldElement utilisés par le client.
  *
  * Conteneur global contenant toutes les données serveurs dont le client a besoin.
  * Demande automatiquement les informations nécessaires si besoin est.
  */
class Store : public QObject
{
    Q_OBJECT
public:
    static void updatePosition(quint64 code, quint64 id, const Position &pos);
    static void updatePositionPlayer(quint64 id, const Position &pos);
    static void updatePositionBuilding(quint64 id, const Position &pos);
    static void updatePositionObject(quint64 id, const Position &pos);
    static void updatePositionStaticObject(quint64 id, const Position &pos);

    static void setInformation(WorldElement* el);
    static void setInformationPlayer(gPlayer* p);
    static void setInformationBuilding(gBuilding *g);
    static void setInformationObject(gObject* o);
    static void setInformationStaticObject(gStaticObject* s);

    static Store& instance();

private:
    Store();

    static Store s_instance;

    QMap<quint64, cPlayer*> m_players;
    QMap<quint64, gBuilding*> m_building;
    QMap<quint64, gObject*> m_objetcs;
    QMap<quint64, gStaticObject*> m_staticobjects;

    void emitMessage(const Message::Message& message);

signals:
    void sendMessage(const Message::Message& message);
    void newElement(cWorldElement*);
};

#endif // STORE_HPP
