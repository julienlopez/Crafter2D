#include "cplayer.hpp"
#include "store.hpp"

cPlayer::cPlayer(quint64 id, QGraphicsItem* parent): QObject(&Store::instance()), cWorldElement(parent), gPlayer(id)
{
    QVector<QPointF> v;
    v << QPointF(-0.5,1) << QPointF(-1,0) << QPointF(-0.5,-1) << QPointF(0.5,-1) << QPointF(1,0) << QPointF(0.5,1);
    setPolygon(QPolygonF(v));
    new QGraphicsLineItem(0,0,1,0,this);
    connect(&inventory(), SIGNAL(modified()), this, SIGNAL(modified()));
}

cPlayer::cPlayer(gPlayer* player): QObject(&Store::instance()), cWorldElement(), gPlayer(*player)
{
    QVector<QPointF> v;
    v << QPointF(-0.5,1) << QPointF(-1,0) << QPointF(-0.5,-1) << QPointF(0.5,-1) << QPointF(1,0) << QPointF(0.5,1);
    setPolygon(QPolygonF(v));
    new QGraphicsLineItem(0,0,1,0,this);
    connect(&inventory(), SIGNAL(modified()), this, SIGNAL(modified()));
}

void cPlayer::setPosition(const Position& p) {
    gPlayer::setPosition(p);
    cWorldElement::setPosition(p);
}

Position cPlayer::position() const
{
    return gPlayer::position();
}
