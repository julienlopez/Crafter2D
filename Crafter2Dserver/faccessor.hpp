#ifndef FACCESSOR_HPP
#define FACCESSOR_HPP

#include "dataaccessor.hpp"
#include "sworldelement.hpp"

#include <QObject>
#include <QMap>

#include <typeinfo>
#include <cassert>

#include <QDebug>

template<class G, class S> class fAccessor
{
public:
    typedef QMap<quint64, S*> map;

    fAccessor(){}

    virtual ~fAccessor()
    {
        qDebug() << "destruction de l'accesseur" << typeid(S).name();
        if(buffer.size() == 0) return;
        qDebug() << "accesseur non-vide";
        S* s;
        foreach(s, buffer) qDebug() << "fuite memoire: " << s->id();
    }

    S* get(quint64 id)
    {
        if(buffer.keys().contains(id)) return buffer[id];
        S* s = S::load(id);
        assert(s);
        buffer[id] = s;
        return s;
    }

    QList<quint64> getIdByPosition(const Position& pos, double distance)
    {
        QList<quint64> res;
        S* s;
        foreach(s, buffer)
            if(s->position().distance(pos) >= distance) res << s->id();
        return res;
    }

    void clear()
    {
        S* s;
        foreach(s, buffer)
        {
            DataAccessor::save(s, true);
            buffer.remove(buffer.key(s));
        }
    }

protected:
    map buffer;
};

#endif // FACCESSOR_HPP
