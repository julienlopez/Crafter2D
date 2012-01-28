#include "inventory.hpp"

const QStringList Inventory::itemLabels = QStringList() << "";

Inventory::Inventory()
{
}

quint32 Inventory::operator()(Item i) const
{
    Q_ASSERT(i < (quint32)itemLabels.size());
    if(m_invent.keys().contains(i)) return m_invent[i];
    return 0;
}

void Inventory::operator()(Item i, quint32 n)
{
    Q_ASSERT(i < (quint32)itemLabels.size());
    m_invent[i] = n;
}
