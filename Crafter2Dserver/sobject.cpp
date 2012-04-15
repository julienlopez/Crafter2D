#include "sobject.hpp"

sObject::sObject(quint64 id): gObject(id)
{}

sObject::~sObject()
{

}

void sObject::save()
{

}

sObject* sObject::load(quint64 id) throw(DataAccessor::Exception)
{
    return 0;
}
