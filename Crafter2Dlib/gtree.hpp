#ifndef GTREE_HPP
#define GTREE_HPP

#include <gStaticObject>

class gTree : virtual public gStaticObject
{
public:
    gTree(quint64 id);

    QString nom() const;
    quint32 max() const;

    void setNom(QString nom);
    void setMax(quint32 max);

    static const Type s_type = 1;

    Type type() const;

private:
    QString m_nom;
    quint32 m_max;
};

#endif // GTREE_HPP
