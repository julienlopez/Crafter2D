#ifndef NEARBYOBJECTS_HPP
#define NEARBYOBJECTS_HPP

#include "screen.hpp"

namespace Message {
namespace Screen {

class NearbyObjects : public Screen
{
    Q_OBJECT
public:
    typedef QList<quint64> type_list;

    explicit NearbyObjects();

    static Message* extract(QDataStream& in);
    virtual QDataStream& serialize(QDataStream& out) const;

    static const quint64 s_id = 5008;
    
    type_list buildings() const;
    type_list objects() const;
    type_list staticObjects() const;

private:
    type_list m_buildings;
    type_list m_objects;
    type_list m_staticObjects;
};

}
}

#endif // NEARBYOBJECTS_HPP
