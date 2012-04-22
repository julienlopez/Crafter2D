#ifndef FACTORY_HPP
#define FACTORY_HPP

#include <Utils/Singleton>

#include <QDataStream>

#include <map>
#include <sstream>
#include <stdexcept>

namespace Utils {

template<typename IdentifierType, class T> class DefaultFactoryError
{
protected:
    static T* onUnknownType(IdentifierType i)
    {
        std::ostringstream oss;
        oss << "Type inconnu " << i;
        throw std::runtime_error(oss.str());
    }
};

template< class T, typename IdentifierType,
          class ProductCreator = T*(*)(QDataStream&),
          template<class, typename> class FactoryErrorPolicy = DefaultFactoryError >
class Factory : public Singleton<Factory<T, IdentifierType> >, public FactoryErrorPolicy<IdentifierType, T>
{
    friend class Singleton<Factory<T, IdentifierType> >;
public:
    typedef std::map<IdentifierType, ProductCreator> type_map;

    T* creer(IdentifierType type, QDataStream& stream)
    {
        typename type_map::const_iterator i = m_table.find(type);
        if(i != m_table.end()) return i->second(stream);
        return onUnknownType(type);
    }

    bool registerClasse(IdentifierType i, ProductCreator callback)
    {
        return m_table.insert(typename type_map::value_type(i, callback)).second;
    }

    bool unregisterClasse(IdentifierType i)
    {
        return m_table.erase(i) == 1;
    }

    type_map m_table;
};

}

#endif // FACTORY_HPP
