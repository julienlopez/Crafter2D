#ifndef CWORLDELEMENT_HPP
#define CWORLDELEMENT_HPP

#include <Position>

#include <QGraphicsItem>

/**
  * \brief spécialisation de la classe WorldElement pour le client.
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

protected:
    cWorldElement();
    void init();
};

#endif // CWORLDELEMENT_HPP
