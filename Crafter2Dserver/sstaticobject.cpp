#include "sstaticobject.hpp"
#include "stree.hpp"

#include <QSqlQuery>
#include <QVariant>

#include <cassert>

sStaticObject::sStaticObject(quint64 id): gStaticObject(id)
{}

sStaticObject::~sStaticObject()
{}

void sStaticObject::save()
{
}

sStaticObject* sStaticObject::load(quint64 id) throw(DataAccessor::Exception)
{
    QSqlQuery q("SELECT type, position, data FROM staticobject WHERE id=" + QString::number(id));
    if(!q.exec()) throw DataAccessor::Exception("Impossible d'executer la requetes");
    if(q.size() != 1) throw DataAccessor::Exception("Erreur de base de données");

    q.first();
    bool convert = true;
    unsigned int type = q.value(0).toUInt(&convert);
    if(!convert) throw DataAccessor::Exception("conversion du type invalide");

    sStaticObject* res = instanciate(type, id);
    assert(res);

    Position p(q.value(1).toString());
    if(!p.isValid()) throw DataAccessor::Exception("position invalide");
    res->setPosition(p);

    if(!p.isValid()) throw DataAccessor::Exception("position invalide");
    if(!res->setData(q.value(2).toString())) throw DataAccessor::Exception("données invalides");

    return res;
}

sStaticObject* sStaticObject::instanciate(Type type, quint64 id)
{
    if(type == sTree::s_type) return new sTree(id);
    return 0;
}
