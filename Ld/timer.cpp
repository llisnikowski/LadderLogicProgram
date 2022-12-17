#include "timer.hpp"
#include <QPainter>
#include "painterLd.hpp"
#include "type.hpp"

namespace Ld {

Timer::Timer(QQuickItem *parent)
    :Output{parent}, type_{this}, time_{this}
{
    addProperty(&type_);
    type_.setModel({"Imp1", "Imp2", "Ton", "Tof", "Imp3", "Tof2", "Gen"});
    QObject::connect(&type_, &LdProperty::ComboboxField::valueChanged,
                     this, &QQuickItem::update);
    QObject::connect(&type_, &LdProperty::ComboboxField::itemFocus,
                     this, [this](bool focus){if(focus) emit clicked();});
    addProperty(&time_);
}

Base *Timer::clone(QQuickItem *parent)
{
    Timer *copyObject = new Timer{parent};
    copyObject->address_ = this->address_;
    copyObject->type_ = this->type_;
    copyObject->time_ = this->time_;
    return copyObject;
}

void Timer::paint(QPainter *painter)
{
    PainterLd painterLd{painter, size()};
    painter->setPen(QPen(Qt::white, 2));
    painterLd.drawCoil();
    painterLd.printCenterLetter('T');

    if(selected_){
        painter->setPen(QPen(Qt::black, 2));
        painterLd.drawFrame();
    }
}

Type Timer::getType() const
{
    return Type::Timer;
}

QByteArray Timer::getData() const
{
    QByteArray itemData;
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);
    dataStream << QString("Ld") << static_cast<int>(getType()) << address_
               << type_ << time_;
    return itemData;
}


} //namespace Ld
