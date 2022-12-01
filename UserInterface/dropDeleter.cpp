#include "dropDeleter.hpp"

DropDeleter::DropDeleter(QObject *parent)
    : Ld::DropValidator{parent}
{
}

Qt::DropAction DropDeleter::valid(const QByteArray &dragArrayData)
{
    return Qt::DropAction::MoveAction;
}

void DropDeleter::doAction(const QByteArray &dragArrayData)
{
}
