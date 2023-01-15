#ifndef POSITION_HPP
#define POSITION_HPP

#include <QDataStream>

struct Position
{
    Position(int line=0, int x=0);
    int line;
    int x;
    Position operator+(Position p2);
    bool operator==(const Position &p2);
};

QDataStream &operator<<(QDataStream &stream, const Position &position);
QDataStream &operator>>(QDataStream &stream, Position &position);


#endif // POSITION_HPP
