#ifndef WORLDELEMENT_HPP
#define WORLDELEMENT_HPP

#include <QtGlobal>

class WorldElement
{
public:
    quint64 id() const;

protected:
    WorldElement(quint64 id);

private:
    quint64 m_id;
};

#endif // WORLDELEMENT_HPP
