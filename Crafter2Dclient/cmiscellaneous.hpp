#ifndef CMISCELLANEOUS_HPP
#define CMISCELLANEOUS_HPP

#include "cworldelement.hpp"

class cMiscellaneous : public QObject, public cWorldElement
{
    Q_OBJECT
public:
    explicit cMiscellaneous(quint64 id, QGraphicsItem* parent);
    
signals:
    
public slots:
    
};

#endif // CMISCELLANEOUS_HPP
