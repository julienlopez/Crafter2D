#ifndef FACCESSOR_HPP
#define FACCESSOR_HPP

#include "dataaccessor.hpp"
#include "sworldelement.hpp"

#include <QObject>
#include <QMap>

#include <typeinfo>
#include <QDebug>

template<class G, class S> class fAccessor
{
public:
    typedef QMap<quint64, S*> map;

    fAccessor(){}

    virtual ~fAccessor()
    {
        qDebug() << "destruction de l'accesseur" << typeid(S).name();
        /*
        while(!buffer.empty())
        {
            DataAccessor::save(buffer.begin().value(), true);
            //buffer.remove(buffer.begin().key());
        }
        */

        S* s;
        foreach(s, buffer) DataAccessor::save(s, true);
    }

    G* get(quint64 id)
    {
        if(buffer.keys().contains(id)) return buffer[id];
        S* s = new S(id);
        buffer[id] = s;
        return s;
    }

protected:
    map buffer;
};

#endif // FACCESSOR_HPP
