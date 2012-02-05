#include "inventory.hpp"

const QStringList Inventory::itemLabels = QStringList() << "terre" << "sable" << "boue" << "argile";

Inventory::Inventory()
{}

Inventory::Inventory(const Inventory& i)
{
    m_invent = i.m_invent;
}

Inventory& Inventory::operator=(const Inventory& i)
{
    m_invent = i.m_invent;
    emit modified();
    return *this;
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
    emit modified();
}

QList<Inventory::Item> Inventory::keys() const
{
    return m_invent.keys();
}

QDataStream& operator >>(QDataStream& in, Inventory& inv)
{
    in >> inv.m_invent;
    return in;
}

QDataStream& operator <<(QDataStream& out, const Inventory& inv)
{
    out << inv.m_invent;
    return out;
}

QString Inventory::toString() const
{
    QString res = "[";
    for(type_container::ConstIterator i = m_invent.begin(); i != m_invent.end(); ++i)
        res += "{" + QString::number(i.key()) + "," + QString::number(i.value()) + "},";
    if(res.size() > 1) res.chop(1);
    return res+"]";
}

Inventory Inventory::fromString(QString str)
{
    Inventory res;
    if(str.isEmpty()) return res;
    Q_ASSERT(str.startsWith("[") && str.endsWith("]"));
    str.remove(0,1);
    str.chop(1);
    QStringList items = str.split(',');
    foreach(QString it, items)
    {
        Q_ASSERT_X(it.startsWith('{') && it.endsWith('}') && it.contains(';'), "Inventory::fromString", QString("Erreur avec: "+it).toStdString().c_str());
        it.remove(0,1);
        it.chop(1);
        QStringList values = it.split(';');
        Q_ASSERT(values.size() == 2);
        res(values[0].toUInt(), values[1].toUInt());
    }
    return res;
}
