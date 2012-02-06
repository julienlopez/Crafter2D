#include "cworldelement.hpp"
#include "ui/menu/menu.hpp"

#include <Utils>

#include <QGraphicsSceneMouseEvent>

cWorldElement::cWorldElement(QGraphicsItem* parent): QGraphicsPolygonItem(parent), m_menu(0)
{}

cWorldElement::cWorldElement(const QPolygonF& forme, QGraphicsItem* parent): QGraphicsPolygonItem(forme, parent), m_menu(0)
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

UI::Menu* cWorldElement::menu()
{
    if(!m_menu)
    {
        m_menu = new UI::Menu(this);
    }
    return m_menu;
}

void cWorldElement::init()
{
    setPosition(position());
}

void cWorldElement::mousePressEvent(QGraphicsSceneMouseEvent* evt)
{
    Q_UNUSED(evt);
    showMenu();
    evt->accept();
}
