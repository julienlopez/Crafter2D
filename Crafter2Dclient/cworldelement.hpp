#ifndef CWORLDELEMENT_HPP
#define CWORLDELEMENT_HPP

#include <Position>

#include <QGraphicsItem>

/**
  * \brief sp�cialisation de la classe WorldElement pour le client.
  *
  *
  */
class cWorldElement : public QGraphicsItem
{
public:
    cWorldElement();

    virtual void setPosition(const Position& p);
};

#endif // CWORLDELEMENT_HPP
