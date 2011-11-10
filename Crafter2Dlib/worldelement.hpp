#ifndef WORLDELEMENT_HPP
#define WORLDELEMENT_HPP

#include <QtGlobal>
#include <QDataStream>

class WorldElement
{
public:
    quint64 id() const;

protected:
    WorldElement(quint64 id);

    virtual void serialize(QDataStream& out) const;
    static WorldElement* extract(QDataStream& in);
private:
    quint64 m_id;
};

#endif // WORLDELEMENT_HPP
