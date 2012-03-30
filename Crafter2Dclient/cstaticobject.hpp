#ifndef CSTATICOBJECT_HPP
#define CSTATICOBJECT_HPP

#include <gStaticObject>

#include "cworldelement.hpp"

#include <QObject>

class QGraphicsItem;

class cStaticObject : public QObject, public cWorldElement, public gStaticObject
{
    Q_OBJECT
public:
    cStaticObject(quint64 id, QGraphicsItem* parent);
    cStaticObject(gStaticObject* staticObject);
    
signals:
    
public slots:
    
};

#endif // CSTATICOBJECT_HPP
