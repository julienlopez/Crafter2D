#include "cworldelement.hpp"
#include "ui/menu/menu.hpp"

#include <Utils>

#include <QGraphicsSceneMouseEvent>

#include <QDebug>

cWorldElement::cWorldElement(QGraphicsItem* parent): QGraphicsItem(parent), m_menu(0)
{}

cWorldElement::cWorldElement(): m_menu(0) {
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
    qDebug() << "cWorldElement::mousePressEvent";
    showMenu();
    evt->accept();
}
