#ifndef WORLDELEMENT_HPP
#define WORLDELEMENT_HPP

#include <QtGlobal>
#include <QDataStream>

class WorldElement
{
public:
    quint64 id() const;

    virtual void serialize(QDataStream& out) const;
    static WorldElement* extract(QDataStream& in);

protected:
    WorldElement(quint64 id);

private:
    quint64 m_id;
};

#endif // WORLDELEMENT_HPP
