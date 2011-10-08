#include "screen.hpp"

#include <QPainter>

#include <cassert>

#include <QDebug>

Screen::Screen(QWidget *parent) :
    QWidget(parent)
{
    setAutoFillBackground(true);
    setPalette(QPalette(Qt::white, Qt::black));
}

void Screen::paintEvent(QPaintEvent* evt)
{
    Q_UNUSED(evt)
    QPainter p(this);
    if(!position.isValid())
    {
        p.setPen(Qt::white);
        p.drawText(width()/2-100, height()/2-50,200,100, Qt::AlignCenter, "chargement en cours");
        return;
    }
}

void Screen::handleMessage(Message* message)
{
    assert(message->id() >= 5000);
    qDebug() << "traitement du message";
}
