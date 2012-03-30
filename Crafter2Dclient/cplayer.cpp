#include "cplayer.hpp"
#include "store.hpp"
#include "ui/menu/menu.hpp"
#include "ui/menu/textentry.hpp"

#include <Utils>

#include <QBrush>
#include <QFont>
#include <QPainter>

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
    return QRectF(-2,-2,4,4);
}

void cPlayer::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    painter->save();

    painter->setPen(QPen(Qt::black));
    painter->setBrush(Qt::lightGray);

    QVector<QPointF> v;
    v << QPointF(-0.5,1) << QPointF(-1,0) << QPointF(-0.5,-1) << QPointF(0.5,-1) << QPointF(1,0) << QPointF(0.5,1);
    painter->drawConvexPolygon(QPolygonF(v));
    painter->drawLine(0,0,1,0);

    painter->restore();
}

void cPlayer::showMenu()
{
    UI::Menu* m = menu();
    Q_ASSERT(m);
    qDebug() << "showMenu()";
    //m->rotate(position().angle() - m->rotation());
    if(m->empty()) {
        m->addItem(new UI::TextEntry(pseudo()));
    }
    m->ouvrir();
}

void cPlayer::init()
{
    connect(&inventory(), SIGNAL(modified()), this, SIGNAL(modified()));
    m_label = new QGraphicsSimpleTextItem(parentItem());
    m_label->setText(pseudo());
    m_label->setBrush(Qt::black);
    m_label->setFont(QFont("arial", 1));
}
