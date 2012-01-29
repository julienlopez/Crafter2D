#include "inventorydock.hpp"
#include "store.hpp"
#include "cplayer.hpp"

#include <QListWidget>

#include <QDebug>

InventoryDock::InventoryDock(quint64 idPlayer, QWidget *parent) :
    QDockWidget(parent)
{
    m_player = Store::getPlayer(idPlayer);
    if(m_player) connect(&m_player->inventory(), SIGNAL(modified()), this, SLOT(maj()));
    else qDebug() << "aucun player";

    view = new QListWidget();
    setWidget(view);
}

void InventoryDock::maj()
{
    if(!m_player) return;
    view->clear();
    const Inventory& i = m_player->inventory();
    QList<Inventory::Item> keys = i.keys();
    foreach(Inventory::Item it, keys)
        view->addItem(Inventory::itemLabels.at(it)+": "+QString::number(i(it)));
}
