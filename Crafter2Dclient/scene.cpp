#include "scene.hpp"

#include <Message/Screen/SetPosition>

#include <QTimer>
#include <QGraphicsTextItem>
#include <QGraphicsSceneMouseEvent>

#include <QVector2D>

#include <cassert>

#include <QDebug>

Scene::Scene(QObject *parent) :
    QGraphicsScene(-1000, -1000, 2000, 2000, parent)
{
    timer = new QTimer(this);
    timer->setInterval(dt);
    connect(timer, SIGNAL(timeout()), this, SLOT(maj()));

    if(!position.isValid()) addItem(new QGraphicsTextItem("Chargement en cours..."));
}

Position Scene::player() const
{
    return position;
}

void Scene::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    QPointF click = event->scenePos();
    qDebug() << "clique sur" << click;
    togo.clear();
    togo << click;
}

void Scene::setPosition(const Position& p)
{
    if(!p.isValid()) return;
    qDebug() << "setPosition " << p.position();
    if(!position.isValid())
    {
        clear();
        m_root = new QGraphicsLineItem;
        addItem(m_root);
        QGraphicsLineItem* it = new QGraphicsLineItem(-1000,0,1000,0, m_root);
        it->setPen(QPen(Qt::red));
        addItem(it);
        it = new QGraphicsLineItem(0,1000,0,-1000, m_root);
        it->setPen(QPen(Qt::red));
        addItem(it);
        QGraphicsRectItem* ite = new QGraphicsRectItem(-1,-1,2,2, m_root);
        ite->setPen(QPen(Qt::blue));
        addItem(ite);
        QVector<QPointF> v;
        v << QPointF(-0.5,1) << QPointF(-1,0) << QPointF(-0.5,-1) << QPointF(0.5,-1) << QPointF(1,0) << QPointF(0.5,1);
        m_player = new QGraphicsPolygonItem(QPolygonF(v),m_root);
        m_player->setPos(p.position());
        //addItem(m_player);
        timer->start();
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

void Scene::maj()
{
    if(togo.isEmpty() || !position.isValid()) return;
    QVector2D reste(togo.at(0)-position.position());
    QVector2D u = reste.normalized();
    double vitesse = 2;
    if((u*vitesse*dt).toPointF().manhattanLength() > (togo.at(0)-position.position()).manhattanLength())
    {
        position.position() = togo.at(0);
        togo.removeFirst();
    }
    else position.position() += (u*vitesse*dt).toPointF();
    m_player->setPos(position.position());
    emit newPosition(position);
}
