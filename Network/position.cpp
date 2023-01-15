#include "position.hpp"


Position::Position(int line, int x)
    :line{line}, x{x}
{}

Position Position::operator+(Position p2){
    return {this->line + p2.line, this->x + p2.x};
}

bool Position::operator==(const Position &p2)
{
    return this->line == p2.line && this->x == p2.x;
}

QDataStream &operator<<(QDataStream &stream, const Position &position)
{
    stream << position.line << position.x;
    return stream;
}


QDataStream &operator>>(QDataStream &stream, Position &position)
{
    stream >> position.line >> position.x;
    return stream;
}
