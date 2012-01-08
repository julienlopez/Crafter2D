#include "store.hpp"
#include "cplayer.hpp"

#include <gBuilding>
#include <gObject>
#include <gStaticObject>
#include <Message/Screen/RequestObjectInformation>

#include <cassert>

#include <QDebug>

Store Store::s_instance;

void Store::updatePosition(quint64 code, quint64 id, const Position& pos)
{
    switch(code)
    {
    case gPlayer::s_code:
        updatePositionPlayer(id, pos);
        break;
    case gBuilding::s_code:
        updatePositionBuilding(id, pos);
        break;
    case gObject::s_code:
        updatePositionObject(id, pos);
        break;
    case gStaticObject::s_code:
        updatePositionStaticObject(id, pos);
        break;
    }
}

void Store::updatePositionPlayer(quint64 id, const Position &pos)
{
    if(s_instance.m_players.contains(id)) {
        s_instance.m_players[id]->setPosition(pos);
        return;
    }

    s_instance.emitMessage(Message::Screen::RequestObjectInformation(gPlayer::s_code, id));
}

void Store::updatePositionBuilding(quint64 id, const Position &pos)
{
    if(s_instance.m_building.contains(id)) {
        s_instance.m_building[id]->setPosition(pos);
        return;
    }

    s_instance.emitMessage(Message::Screen::RequestObjectInformation(gBuilding::s_code, id));
}

void Store::updatePositionObject(quint64 id, const Position &pos)
{
    if(s_instance.m_objetcs.contains(id)) {
        s_instance.m_objetcs[id]->setPosition(pos);
        return;
    }

    s_instance.emitMessage(Message::Screen::RequestObjectInformation(gObject::s_code, id));
}

void Store::updatePositionStaticObject(quint64 id, const Position &pos)
{
    if(s_instance.m_staticobjects.contains(id)) {
        s_instance.m_staticobjects[id]->setPosition(pos);
        return;
    }

    s_instance.emitMessage(Message::Screen::RequestObjectInformation(gStaticObject::s_code, id));
}

void Store::setInformation(WorldElement* el)
{
    if(gPlayer::s_code == el->code())
    {
        gPlayer* p = dynamic_cast<gPlayer*>(el);
        assert(p);
        setInformationPlayer(p);
        return;
    }
    if(gBuilding::s_code == el->code())
    {
        gBuilding* b = dynamic_cast<gBuilding*>(el);
        assert(b);
        setInformationBuilding(b);
        return;
    }
    if(gObject::s_code == el->code())
    {
        gObject* o = dynamic_cast<gObject*>(el);
        assert(o);
        setInformationObject(o);
        return;
    }
    if(gStaticObject::s_code == el->code())
    {
        gStaticObject* s = dynamic_cast<gStaticObject*>(el);
        assert(s);
        setInformationStaticObject(s);
        return;
    }
}

void Store::setInformationPlayer(gPlayer* p)
{
    qDebug() << "ajout d'un nouveau player au magasin (" << p->id() << ")";
    if(instance().m_players.keys().contains(p->id())) {
        assert(0&&" a faire ");
    }
    else
    {
        cPlayer* cp = dynamic_cast<cPlayer*>(p);
        if(cp == 0) cp = new cPlayer(p);
        instance().m_players[p->id()] = cp;
        emit instance().newElement(cp);
    }
}

void Store::setInformationBuilding(gBuilding* b)
{
    if(instance().m_building.keys().contains(b->id())) {
        assert(0&&" a faire ");
    }
    else instance().m_building[b->id()] = new gBuilding(*b);
}

void Store::setInformationObject(gObject* o)
{
    if(instance().m_objetcs.keys().contains(o->id())) {
        assert(0&&" a faire ");
    }
    else instance().m_objetcs[o->id()] = new gObject(*o);
}

void Store::setInformationStaticObject(gStaticObject* s)
{
    if(instance().m_staticobjects.keys().contains(s->id())) {
        assert(0&&" a faire ");
    }
    else instance().m_staticobjects[s->id()] = new gStaticObject(*s);
}

Store& Store::instance()
{
    return s_instance;
}

Store::Store()
{}

void Store::emitMessage(const Message::Message& message)
{
    emit sendMessage(message);
}
