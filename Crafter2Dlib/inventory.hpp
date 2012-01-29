#ifndef INVENTORY_HPP
#define INVENTORY_HPP

#include <QMap>
#include <QStringList>

class Inventory : public QObject
{
    Q_OBJECT
public:
    typedef quint32 Item;

    static const QStringList itemLabels;

    Inventory();
    Inventory(const Inventory& i);
    Inventory& operator=(const Inventory& i);

    quint32 operator()(Item) const;
    void operator()(Item, quint32);

    QList<Item> keys() const;

    friend QDataStream& operator >>(QDataStream& in, Inventory& inv);
    friend QDataStream& operator <<(QDataStream& out, const Inventory& inv);

    QString toString() const;
    static Inventory fromString(QString str);

private:
    typedef QMap<Item, quint32> type_container;

    type_container m_invent;

signals:
    void modified();
};

#endif // INVENTORY_HPP
