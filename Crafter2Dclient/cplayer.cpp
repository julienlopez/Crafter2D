#include "cplayer.hpp"

cPlayer::cPlayer(quint64 id, QGraphicsItem* parent): cWorldElement(parent), gPlayer(id)
{
    QVector<QPointF> v;
    v << QPointF(-0.5,1) << QPointF(-1,0) << QPointF(-0.5,-1) << QPointF(0.5,-1) << QPointF(1,0) << QPointF(0.5,1);
    setPolygon(QPolygonF(v));
}

cPlayer::cPlayer(gPlayer* player):
    cWorldElement(), gPlayer(*player)
{
    QVector<QPointF> v;
    v << QPointF(-0.5,1) << QPointF(-1,0) << QPointF(-0.5,-1) << QPointF(0.5,-1) << QPointF(1,0) << QPointF(0.5,1);
    setPolygon(QPolygonF(v));
}

void cPlayer::setPosition(const Position& p) {
    gPlayer::setPosition(p);
    cWorldElement::setPosition(p);
}

Position cPlayer::position() const
{
    return gPlayer::position();
}
