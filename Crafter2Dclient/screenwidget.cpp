#include "screenwidget.hpp"

#include <Message/Screen/SetPosition>

#include <QPainter>
#include <QMessageBox>

#include <cassert>

#include <QDebug>

ScreenWidget::ScreenWidget(QWidget *parent) :
    QWidget(parent)
{
    setAutoFillBackground(true);
    setPalette(QPalette(Qt::white, Qt::black));
}

void ScreenWidget::paintEvent(QPaintEvent* evt)
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

void ScreenWidget::setPosition(const Position& p)
{
    position = p;
    emit newPosition(p);
}

void ScreenWidget::handleMessage(Message::Message* message)
{
    assert(message->id() >= 5000);
    qDebug() << "traitement du message";
    if(message->id() == 5002)
    {
        const Message::Screen::SetPosition* p = qobject_cast<const Message::Screen::SetPosition*>(message);
        assert(p != 0);
        setPosition(p->position());
    }
}
