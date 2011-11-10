#include "idset.hpp"

IdSet::Pair::Pair(Client* f, Client* s): first(f), second(s)
{}

bool IdSet::Pair::operator ==(Client* i) const
{
    return first == i || second == i;
}

bool IdSet::Pair::operator ==(const Pair& p) const
{
    return (first == p.first && second == p.second) || (second == p.first && first == p.second);
}

Client* IdSet::Pair::get(Client* i)
{
    if(i == first) return second;
    if(i == second) return first;
    return 0;
}

uint qHash(const IdSet::Pair& p)
{
    return (uint)p.first ^ (uint)p.second;
}

IdSet::IdSet()
{
}

void IdSet::insert(Client* i, Client* j)
{
    set.insert(Pair(i,j));
}
