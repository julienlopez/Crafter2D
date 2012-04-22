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

    virtual void setPosition(const Position& p);
    virtual Position position() const;

    QRectF boundingRect() const;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);

protected:
    void showMenu();

    static cStaticObject* instanciate(gStaticObject* staticobject);
    static cStaticObject* instanciate(gStaticObject::Type type, quint64 id);
    
signals:
    
public slots:
    
};

#endif // CSTATICOBJECT_HPP
