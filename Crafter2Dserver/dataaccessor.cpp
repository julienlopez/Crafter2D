#include "dataaccessor.hpp"

DataAccessor DataAccessor::m_instance;

DataAccessor& DataAccessor::instance() {
    return m_instance;
}

DataAccessor::DataAccessor(): QObject()
{
}
