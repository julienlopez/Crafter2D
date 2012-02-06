#ifndef CWORLDELEMENT_HPP
#define CWORLDELEMENT_HPP

#include <Position>

#include <QGraphicsItem>

class Menu;

/**
  * \brief sp�cialisation de la classe WorldElement pour le client.
  *
  *
  */
class cWorldElement : public QGraphicsPolygonItem
{
public:
    cWorldElement(QGraphicsItem* parent);
    cWorldElement(const QPolygonF& forme, QGraphicsItem* parent);

    virtual void setPosition(const Position& p);
    virtual Position position() const =0;

    Menu* menu();

protected:
    cWorldElement();
    void init();

    void mousePressEvent(QGraphicsSceneMouseEvent* evt);

    virtual void showMenu() =0;

private:
    Menu* m_menu;
};

#endif // CWORLDELEMENT_HPP
