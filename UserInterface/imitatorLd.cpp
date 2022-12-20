#include "imitatorLd.hpp"
#include "painterLd.hpp"
#include <QPainter>

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
    Ld::PainterLd painterLd{painter, size()};
    painter->setPen(QPen(Qt::white, 2));
    if(type_ >= Ld::Type::Input){
        painterLd.drawContact();
        if(type_ == Ld::Type::Weektimer){
            painterLd.printCenterLetter('Z');
        }
    }
    else if(type_ >= Ld::Type::Output){
        painterLd.drawCoil();
        if(type_ == Ld::Type::Timer){
            painterLd.printCenterLetter('T');
        }
        else if(type_ == Ld::Type::Counter){
            painterLd.printCenterLetter('C');
        }
        else if(type_ == Ld::Type::Text){
            painterLd.printCenterLetter('X');
        }
    }
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



