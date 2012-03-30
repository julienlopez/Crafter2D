#include "cworldelement.hpp"
#include "ui/menu/menu.hpp"

#include <Utils>

#include <QGraphicsSceneMouseEvent>

#include <QDebug>

cWorldElement::cWorldElement(QGraphicsItem* parent): QGraphicsItem(parent), m_menu(0)
{
    m_menu = new UI::Menu(this);
    m_menu->fermer();
}

cWorldElement::cWorldElement(): m_menu(0)
{
    m_menu = new UI::Menu(this);
    m_menu->fermer();
}

void cWorldElement::setPosition(const Position& p)
{
    setPos(p.position());
    setRotation(180*p.angle()/Utils::PI);
}

UI::Menu* cWorldElement::menu()
{
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
