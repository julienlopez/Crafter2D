#include "inventory.hpp"

#include <cassert>

const QStringList Inventory::itemLabels = QStringList() << "";

Inventory::Inventory()
{
}

quint32 Inventory::operator()(Item i) const
{
    assert(i < (quint32)itemLabels.size());
    if(m_invent.keys().contains(i)) return m_invent[i];
    return 0;
}

void Inventory::operator()(Item i, quint32 n)
{
    assert(i < (quint32)itemLabels.size());
    m_invent[i] = n;
}
