#include "stree.hpp"

#include <Utils/JsonParser>

#include <QStringList>

sTree::sTree(quint64 id): gStaticObject(id), gTree(id), sStaticObject(id)
{
}

bool sTree::setData(QString data)
{
    if(data.isEmpty()) return false;

    bool res = true;
    Utils::JsonParser p;
    QVariantMap d = p.parse(data, &res);
    if(!res) return false;

    QStringList keys = d.keys();
    if(!keys.contains("nom") || !keys.contains("max")) return false;
    setNom(d["nom"].toString());
    setMax(d["max"].toUInt());

    return true;
}
