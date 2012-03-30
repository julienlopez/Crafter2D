#include "cstaticobject.hpp"
#include "store.hpp"

cStaticObject::cStaticObject(quint64 id, QGraphicsItem* parent) : QObject(&Store::instance()), cWorldElement(parent), gStaticObject(id)
{
}

cStaticObject::cStaticObject(gStaticObject* staticObject): QObject(&Store::instance()), cWorldElement(), gStaticObject(*staticObject)
{

}
