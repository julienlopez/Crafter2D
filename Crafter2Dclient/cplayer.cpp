#include "cplayer.hpp"
#include "store.hpp"
#include "ui/menu/menu.hpp"
#include "ui/menu/textentry.hpp"

#include <Utils>

#include <QBrush>
#include <QFont>

#include <cmath>

#include <QDebug>

cPlayer::cPlayer(quint64 id, QGraphicsItem* parent): QObject(&Store::instance()), cWorldElement(parent), gPlayer(id)
{
    init();
}

cPlayer::cPlayer(gPlayer* player): QObject(&Store::instance()), cWorldElement(), gPlayer(*player)
{
    init();
}

void cPlayer::setPosition(const Position& p) {
    gPlayer::setPosition(p);
    cWorldElement::setPosition(p);

    m_label->setText(pseudo());
    m_label->setPos(p.position().x() - m_label->boundingRect().width()/2, p.position().y() - 5);
}

Position cPlayer::position() const
{
    return gPlayer::position();
}

QRectF cPlayer::boundingRect() const
{
    return QRectF(-10,-10,20,20);
}

void cPlayer::showMenu()
{
    UI::Menu* m = menu();
    Q_ASSERT(m);
    qDebug() << "showMenu()";
    m->addItem(new UI::TextEntry(pseudo()));
}

void cPlayer::init()
{
    QVector<QPointF> v;
    v << QPointF(-0.5,1) << QPointF(-1,0) << QPointF(-0.5,-1) << QPointF(0.5,-1) << QPointF(1,0) << QPointF(0.5,1);
    setPolygon(QPolygonF(v));
    new QGraphicsLineItem(0,0,1,0,this);
    connect(&inventory(), SIGNAL(modified()), this, SIGNAL(modified()));
    m_label = new QGraphicsSimpleTextItem(parentItem());
    m_label->setText(pseudo());
    m_label->setBrush(Qt::black);
    m_label->setFont(QFont("arial", 1));
}
