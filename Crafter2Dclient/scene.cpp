#include "scene.hpp"

#include <Utils>
#include <Message/Screen/SetPosition>
#include <Message/Screen/SendPosition>

#include <QTimer>
#include <QGraphicsTextItem>
#include <QGraphicsSceneMouseEvent>
#include <QVector2D>

#include <cmath>
#include <cassert>

#include <QDebug>

Scene::Scene(QObject *parent) :
    QGraphicsScene(-1000, -1000, 2000, 2000, parent)
{
    timer = new QTimer(this);
    timer->setInterval(dt);
    connect(timer, SIGNAL(timeout()), this, SLOT(maj()));

    timer_sendPos = new QTimer(this);
    timer_sendPos->setInterval(100);
    connect(timer_sendPos, SIGNAL(timeout()), this, SLOT(sendPosition()));

    if(!position.isValid()) addItem(new QGraphicsTextItem("Chargement en cours..."));
}

Position Scene::player() const
{
    return position;
}

void Scene::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    QPointF click = event->scenePos();
    togo.clear();
    togo << click;
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
        QVector<QPointF> v;
        v << QPointF(-0.5,1) << QPointF(-1,0) << QPointF(-0.5,-1) << QPointF(0.5,-1) << QPointF(1,0) << QPointF(0.5,1);
        m_player = new QGraphicsPolygonItem(QPolygonF(v),m_root);
        it = new QGraphicsLineItem(0,0,1,0,m_player);
        m_player->setPos(p.position());
        timer->start();
        timer_sendPos->start();
    }
    old_pos = position;
    position = p;
    emit newPosition(p);
}

void Scene::handleMessage(Message::Message* message)
{
    assert(message->id() >= 5000);
    if(message->id() == 5002)
    {
        const Message::Screen::SetPosition* p = qobject_cast<const Message::Screen::SetPosition*>(message);
        assert(p != 0);
        setPosition(p->position());
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
    m_player->setPos(position.position());
    m_player->setRotation(180*position.angle()/Utils::PI);
    emit newPosition(position);
}

void Scene::sendPosition()
{
    if(position == old_pos) return;
    emit message(Message::Screen::SendPosition(position));
    old_pos = position;
}
