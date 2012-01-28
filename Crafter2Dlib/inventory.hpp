#ifndef INVENTORY_HPP
#define INVENTORY_HPP

#include <QMap>
#include <QStringList>

class Inventory
{
public:
    typedef quint32 Item;

    static const QStringList itemLabels;

    Inventory();

    quint32 operator()(Item) const;
    void operator()(Item, quint32);



private:
    QMap<Item, quint32> m_invent;
};

#endif // INVENTORY_HPP
