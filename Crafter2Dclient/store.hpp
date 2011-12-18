#ifndef STORE_HPP
#define STORE_HPP

class Store
{
public:
    static void updatePosition(quint64 id, const Position& pos);

private:
    Store();
    static Store& instance();

    static Store s_instance;
};

#endif // STORE_HPP
