#include "position.hpp"

Position::Position(): m_valid(false)
{}

Position::Position(QPoint position): m_valid(false), m_position(position)
{}

bool Position::isValid() const
{
    return m_valid;
}

QPoint Position::position() const
{
    return m_position;
}
