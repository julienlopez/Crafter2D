#include "cworldelement.hpp"

#include <Utils>

cWorldElement::cWorldElement()
{
}

void cWorldElement::setPosition(const Position& p)
{
    setPos(p.position());
    setRotation(180*p.angle()/Utils::PI);
}
