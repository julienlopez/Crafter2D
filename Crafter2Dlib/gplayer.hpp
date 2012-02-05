#ifndef GPLAYER_HPP
#define GPLAYER_HPP

#include <WorldElement>
#include <Inventory>

class gPlayer : public WorldElement
{
public:
    gPlayer(quint64 id, const QString& pseudo = QString());

    static const quint64 s_code = 1;

    virtual void serialize(QDataStream& out) const;
    static gPlayer* extract(QDataStream& in);

    quint64 code() const;
    QString pseudo() const;

    Inventory& inventory();
    const Inventory& inventory() const;

protected:
    void setPseudo(const QString& pseudo);

private:
    QString m_pseudo;
    Inventory m_inventory;
};

#endif // GPLAYER_HPP
