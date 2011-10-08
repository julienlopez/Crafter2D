#ifndef POSITION_HPP
#define POSITION_HPP

#include <QPoint>

class Position
{
public:
    Position();
    Position(QPoint position);

    bool isValid() const;
    QPoint position() const;

private:
    bool m_valid;
    QPoint m_position;
};

#endif // POSITION_HPP
