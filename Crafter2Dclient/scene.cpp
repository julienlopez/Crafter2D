#include "scene.hpp"
#include "store.hpp"
#include "cplayer.hpp"
#include "generalsettings.hpp"
#include "ui/menu/menu.hpp"

#include <gStaticObject>
#include <Message/Screen/SetPosition>
#include <Message/Screen/SendPosition>
#include <Message/Screen/MajPosition>
#include <Message/Screen/ObjectInformation>
#include <Message/Screen/RequestObjectInformation>
#include <Message/Screen/GetNearbyObjects>
#include <Message/Screen/NearbyObjects>

#include <QTimer>
#include <QGraphicsTextItem>
#include <QGraphicsSceneMouseEvent>
#include <QVector2D>

#include <cmath>

#include <QDebug>

Scene::Scene(quint64 idPlayer, QObject *parent) :
    QGraphicsScene(-1000, -1000, 2000, 2000, parent)
{
    m_idPlayer = idPlayer;
    timer = new QTimer(this);
    timer->setInterval(dt);
    connect(timer, SIGNAL(timeout()), this, SLOT(maj()));

    timer_sendPos = new QTimer(this);
    timer_sendPos->setInterval(100);
    connect(timer_sendPos, SIGNAL(timeout()), this, SLOT(sendPosition()));

    connect(&Store::instance(), SIGNAL(sendMessage(const Message::Message&)), this, SIGNAL(message(const Message::Message&)));
    connect(&Store::instance(), SIGNAL(newElement(cWorldElement*)), this, SLOT(onNewElement(cWorldElement*)));

    if(!position.isValid()) addItem(new QGraphicsTextItem("Chargement en cours..."));

    connect(this, SIGNAL(newPosition(Position)), this, SLOT(onNewPosition(Position)));
}

Position Scene::player() const
{
    return position;
}

void Scene::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    if(UI::Menu::fermerOpenedMenu()) return;
    if(event->button() == Qt::LeftButton) {
        QPointF click = event->scenePos();
        togo.clear();
        togo << click;
    }
    if(event->button() == Qt::RightButton)
    {
        qDebug() << "Scene::click droit";
        togo.clear();
    }
}

void Scene::setPosition(const Position& p)
{
    if(!p.isValid()) return;
    if(!position.isValid())
    {
        clear();
        m_root = new QGraphicsLineItem;
        addItem(m_root);
        QGraphicsLineItem* it = new QGraphicsLineItem(-1000,0,1000,0, m_root);
        it->setPen(QPen(Qt::red));
        it = new QGraphicsLineItem(0,1000,0,-1000, m_root);
        it->setPen(QPen(Qt::red));
        QGraphicsRectItem* ite = new QGraphicsRectItem(-1,-1,2,2, m_root);
        ite->setPen(QPen(Qt::blue));
        m_player = new cPlayer(m_idPlayer, m_root);
        m_player->setPosition(p);
        Store::setInformationPlayer(m_player);
        timer->start();
        timer_sendPos->start();
        emit message(Message::Screen::RequestObjectInformation(gPlayer::s_code, m_idPlayer));
    }
    old_pos = position;
    position = p;
    emit newPosition(p);
}

void Scene::handleMessage(Message::Message* mess)
{
    Q_ASSERT(mess->id() >= 5000);
    if(mess->id() == Message::Screen::SetPosition::s_id)
    {
        const Message::Screen::SetPosition* p = qobject_cast<const Message::Screen::SetPosition*>(mess);
        Q_ASSERT(p);
        setPosition(p->position());
    }
    if(mess->id() == Message::Screen::MajPosition::s_id)
    {
        const Message::Screen::MajPosition* p = qobject_cast<const Message::Screen::MajPosition*>(mess);
        Q_ASSERT(p);
        Store::updatePosition(p->objectCode(), p->objectId(), p->position());
    }
    if(mess->id() == Message::Screen::ObjectInformation::s_id)
    {
        Message::Screen::ObjectInformation* i = qobject_cast<Message::Screen::ObjectInformation*>(mess);
        Q_ASSERT(i);
        Store::setInformation(i->element());
    }
    if(mess->id() == Message::Screen::NearbyObjects::s_id)
    {
        Message::Screen::NearbyObjects* m = qobject_cast<Message::Screen::NearbyObjects*>(mess);
        Q_ASSERT(m);
        Message::Screen::NearbyObjects::type_list staticObjects = m->staticObjects();
        qDebug() << "staticObjects: " << staticObjects;
        quint64 id;
        foreach(id, staticObjects)
            if(!Store::getStaticObjects(id)) emit message(Message::Screen::RequestObjectInformation(gStaticObject::s_code, id));
    }
}

void Scene::maj()
{
    if(togo.isEmpty() || !position.isValid()) return;
    old_pos = position;
    QVector2D reste(togo.at(0)-position.position());
    QVector2D u = reste.normalized();
    double a = atan2(reste.y(), reste.x());
    position.angle() = a;
    double vitesse = 2;
    if((u*vitesse*dt).toPointF().manhattanLength() > (togo.at(0)-position.position()).manhattanLength())
    {
        position.position() = togo.at(0);
        togo.removeFirst();
    }
    else position.position() += (u*vitesse*dt).toPointF();
    m_player->setPosition(position);
    emit newPosition(position);
}

void Scene::sendPosition()
{
    if(position == old_pos) return;
    emit message(Message::Screen::SendPosition(position));
    old_pos = position;
}

void Scene::onNewElement(cWorldElement* el)
{
    if(el->parentItem() != m_root)
        el->setParentItem(m_root);
}

void Scene::onNewPosition(const Position& p)
{
    if(lastNearbyObjectUpdate.isValid() && lastNearbyObjectUpdate.distance(p) < GeneralSettings::distanceToRefreshNearbyObject()) return;
    qDebug() << "onNewPosition(" << p.position() << ")";
    emit message(Message::Screen::GetNearbyObjects(p, GeneralSettings::distanceToLoadNearbyObject()));
    lastNearbyObjectUpdate = p;
}
