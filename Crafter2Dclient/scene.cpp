#include "scene.hpp"

#include <Message/Screen/SetPosition>

#include <QGraphicsTextItem>

#include <cassert>

#include <QDebug>

Scene::Scene(QObject *parent) :
    QGraphicsScene(parent)
{
    if(!position.isValid()) addItem(new QGraphicsTextItem("Chargement en cours..."));
}

void Scene::setPosition(const Position& p)
{
    if(!p.isValid()) return;
    qDebug() << "setPosition " << p.position();
    if(!position.isValid())
    {
        clear();
        QVector<QPointF> v;
        v << QPointF(-0.5,1) << QPointF(-1,0) << QPointF(-0.5,-1) << QPointF(0.5,-1) << QPointF(1,0) << QPointF(0.5,1);
        player = new QGraphicsPolygonItem(QPolygonF(v));
        player->setPos(p.position());
        addItem(player);
    }
    position = p;
    emit newPosition(p);
}

void Scene::handleMessage(Message::Message* message)
{
    assert(message->id() >= 5000);
    qDebug() << "traitement du message";
    if(message->id() == 5002)
    {
        const Message::Screen::SetPosition* p = qobject_cast<const Message::Screen::SetPosition*>(message);
        assert(p != 0);
        setPosition(p->position());
    }
}
