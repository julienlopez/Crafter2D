#ifndef GETNEARBYOBJECTS_HPP
#define GETNEARBYOBJECTS_HPP

#include "screen.hpp"
#include "../../position.hpp"

namespace Message {
namespace Screen {

class GetNearbyObjects : public Screen
{
    Q_OBJECT
public:
    explicit GetNearbyObjects(const Position& position, double distance);
    
    Position position() const;
    double distance() const;

    static Message* extract(QDataStream& in);
    virtual QDataStream& serialize(QDataStream& out) const;

    static const quint64 s_id = 5007;
    
private:
    Position m_position;
    double m_distance;
};

}}

#endif // GETNEARBYOBJECTS_HPP
