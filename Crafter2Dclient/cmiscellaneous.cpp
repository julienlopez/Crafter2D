#include "cmiscellaneous.hpp"
#include "store.hpp"

cMiscellaneous::cMiscellaneous(quint64 id, QGraphicsItem* parent) :
    QObject(&Store::instance()), cWorldElement(parent)
{
}
