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
    ObjectInformation();

    static ObjectInformation* extract(QDataStream& in, quint64 id);
    virtual QDataStream& serialize(QDataStream& out) const;

private:
    WorldElement* m_element;

};

}}

#endif // OBJECTINFORMATION_HPP
