#ifndef IDSET_HPP
#define IDSET_HPP

#include <QSet>

class Client;

class IdSet
{
public:
    class Pair
    {
    public:
        Pair(Client* f, Client* s);

        bool operator ==(Client* i) const;
        bool operator ==(const Pair& p) const;
        Client* get(Client* i);

        friend uint qHash(const Pair& p);

    protected:
        Client* first;
        Client* second;
    };

    IdSet();
    void insert(Client* i, Client* j);

private:
    QSet<Pair> set;
};

#endif // IDSET_HPP
