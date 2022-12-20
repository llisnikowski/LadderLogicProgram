#include "imitatorLd.hpp"



ImitatorLd::ImitatorLd(QQuickItem *parent)
    :Ld::Drag{parent}, type_{}
{
}

Ld::Base *ImitatorLd::clone(QQuickItem *parent)
{
    ImitatorLd *copyObject = new ImitatorLd{parent};
    return copyObject;
}

void ImitatorLd::paint(QPainter *painter)
{

}

Ld::Type ImitatorLd::getType() const
{
    return type_;
}

void ImitatorLd::setType(Ld::Type type)
{
    type_ = type;
}

QByteArray ImitatorLd::getData() const
{
    QByteArray itemData;
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);
    dataStream << QString("Ld") << static_cast<int>(type_);
    return itemData;
}



