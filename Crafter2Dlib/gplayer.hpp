#ifndef GPLAYER_HPP
#define GPLAYER_HPP

#include <WorldElement>
#include <Inventory>

class gPlayer : public WorldElement
{
public:
    gPlayer(quint64 id);

    static const quint64 s_code = 1;

    virtual void serialize(QDataStream& out) const;
    static gPlayer* extract(QDataStream& in);

    quint64 code() const;

    Inventory& inventory();
    const Inventory& inventory() const;

private:
    Inventory m_inventory;
};

#endif // GPLAYER_HPP
