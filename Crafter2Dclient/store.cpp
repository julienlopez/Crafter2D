#include "store.hpp"

Store Store::s_instance;

void Store::updatePosition(quint64 id, const Position& pos) {
    Store& s = instance();
}

Store::Store()
{
}

Store& Store::instance() {
    return s_instance;
}
