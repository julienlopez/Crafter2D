#ifndef OBJECTINFORMATION_HPP
#define OBJECTINFORMATION_HPP

#include "screen.hpp"

class WorldElement;

namespace Message {
namespace Screen {

class ObjectInformation : public Screen
{
    Q_OBJECT
public:
    ObjectInformation(WorldElement* element =0);

    WorldElement* element();

    static Message *extract(QDataStream& in);
    virtual QDataStream& serialize(QDataStream& out) const;

    static const quint64 s_id = 5004;
private:
    WorldElement* m_element;

};

}}

#endif // OBJECTINFORMATION_HPP
