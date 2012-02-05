#include "inventorydock.hpp"
#include "store.hpp"
#include "cplayer.hpp"

#include <QListWidget>
#include <QBasicTimer>
#include <QTimerEvent>

InventoryDock::InventoryDock(quint64 idPlayer, QWidget *parent) :
    QDockWidget(parent), m_idPlayer(idPlayer)
{
    m_timer = 0;
    view = new QListWidget();
    setWidget(view);

    m_player = Store::getPlayer(idPlayer);
    if(m_player) connect(m_player, SIGNAL(modified()), this, SLOT(maj()));
    else {
        m_timer = new QBasicTimer;
        m_timer->start(100, this);
    }
}

void InventoryDock::timerEvent(QTimerEvent* event) {
    if(m_timer && event->timerId() == m_timer->timerId()) maj();
    else QDockWidget::timerEvent(event);
}

void InventoryDock::maj()
{
    if(!m_player) {
        m_player = Store::getPlayer(m_idPlayer);
        if(!m_player) return;
        m_timer->stop();
        delete m_timer;
        m_timer = 0;
        connect(m_player, SIGNAL(modified()), this, SLOT(maj()));
    }

    view->clear();
    const Inventory& i = m_player->inventory();
    QList<Inventory::Item> keys = i.keys();
    foreach(Inventory::Item it, keys)
        view->addItem(Inventory::itemLabels.at(it)+": "+QString::number(i(it)));
}
