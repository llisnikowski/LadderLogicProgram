#include "counter.hpp"
#include <QPainter>
#include "painterLd.hpp"

namespace Ld {

Counter::Counter(QQuickItem *parent)
    :Output{parent}
{
    addProperty(&type_);
    type_.setModel({"Add", "Dir", "Reset"});
    QObject::connect(&type_, &LdProperty::ComboboxField::valueChanged,
                     this, &QQuickItem::update);
    QObject::connect(&type_, &LdProperty::ComboboxField::itemFocus,
                     this, [this](bool focus){if(focus) emit clicked();});
    addProperty(&counter_);
    counter_.setPropertyName("Wartość zadana");
}

Base *Counter::clone(QQuickItem *parent)
{
    Counter *copyObject = new Counter{parent};
    copyObject->address_ = this->address_;
    copyObject->type_ = this->type_;
    copyObject->counter_ = this->counter_;
    return copyObject;
}

void Counter::paint(QPainter *painter)
{
    PainterLd painterLd{painter, size()};
    painter->setPen(QPen(Qt::white, 2));
    painterLd.drawCoil();
    painterLd.printCenterLetter('C');

    if(selected_){
        painter->setPen(QPen(Qt::black, 2));
        painterLd.drawFrame();
    }
}

Type Counter::getType() const
{
    return Type::Counter;
}

QByteArray Counter::getData() const
{
    QByteArray itemData;
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);
    dataStream << QString("Ld") << static_cast<int>(getType()) << address_
               << type_ << counter_;
    return itemData;
}


} //namespace Ld
