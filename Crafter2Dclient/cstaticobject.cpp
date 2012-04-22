#include "cstaticobject.hpp"
#include "store.hpp"
#include "ctree.hpp"

#include <gTree>

cStaticObject::cStaticObject(quint64 id, QGraphicsItem* parent) : QObject(&Store::instance()), cWorldElement(parent), gStaticObject(id)
{
}

cStaticObject::cStaticObject(gStaticObject* staticObject): QObject(&Store::instance()), cWorldElement(), gStaticObject(*staticObject)
{

}

void cStaticObject::setPosition(const Position& p)
{
    gStaticObject::setPosition(p);
    cWorldElement::setPosition(p);
}

Position cStaticObject::position() const
{
    return gStaticObject::position();
}

QRectF cStaticObject::boundingRect() const
{

}

void cStaticObject::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{

}

void cStaticObject::showMenu()
{

}

cStaticObject* cStaticObject::instanciate(gStaticObject* staticobject)
{
    if(staticobject->type() == gTree::s_type) {
        gTree* o = dynamic_cast<gTree*>(staticobject);
        return new cTree(o);
    }
    return 0;
}

cStaticObject* cStaticObject::instanciate(gStaticObject::Type type, quint64 id)
{
    if(type == gTree::s_type) return new cTree(id);
    return 0;
}
