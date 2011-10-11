#ifndef FACCESSOR_HPP
#define FACCESSOR_HPP

#include <QMap>

template<class T> class fAccessor
{
public:
    fAccessor() {}

protected:
    QMap<quint64, T> buffer;
};

#endif // FACCESSOR_HPP
