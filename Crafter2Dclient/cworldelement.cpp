#include "cworldelement.hpp"

#include <Utils>

cWorldElement::cWorldElement(QGraphicsItem* parent): QGraphicsPolygonItem(parent)
{}

cWorldElement::cWorldElement(const QPolygonF& forme, QGraphicsItem* parent): QGraphicsPolygonItem(forme, parent)
{
    init();
}

cWorldElement::cWorldElement() {

}

void cWorldElement::setPosition(const Position& p)
{
    setPos(p.position());
    setRotation(180*p.angle()/Utils::PI);
}

void cWorldElement::init()
{
    setPosition(position());
}

/*
QRectF cWorldElement::boundingRect() const
{
    return QRect();
}

void cWorldElement::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{

}
*/
