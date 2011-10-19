#ifndef FACCESSOR_HPP
#define FACCESSOR_HPP

#include <QObject>
#include <QMap>

#include <QDebug>

template<class G, class S> class fAccessor
{
public:
    fAccessor(){}

    G* get(quint64 id)
    {
        if(buffer.keys().contains(id)) return buffer[id];
        S* s = new S(id);
        buffer[id] = s;
        return s;
    }

protected:
    QMap<quint64, S*> buffer;
};

#endif // FACCESSOR_HPP
