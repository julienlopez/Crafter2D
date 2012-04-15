#include "gtree.hpp"

gTree::gTree(quint64 id): gStaticObject(id)
{
}

QString gTree::nom() const
{
    return m_nom;
}

quint32 gTree::max() const
{
    return m_max;
}

void gTree::setNom(QString nom)
{
    m_nom = nom;
}

void gTree::setMax(quint32 max)
{
    m_max = max;
}
