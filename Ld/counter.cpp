#include "counter.hpp"
#include <QPainter>
#include "painterLd.hpp"
#include <QRegularExpression>

namespace Ld {

Counter::Counter(QQuickItem *parent)
    :Output{parent}, type_{this}, counter_{}
{
    addProperty(&type_);
    type_.setModel({"Add", "Dir", "Reset"});
    QObject::connect(&type_, &LdProperty::ComboboxField::valueChanged,
                     this, &QQuickItem::update);
    QObject::connect(&counter_, &LdProperty::TextField::textValueChanged,
                     this, &QQuickItem::update);
    QObject::connect(&type_, &LdProperty::ComboboxField::itemFocus,
                     this, [this](bool focus){if(focus) emit clicked();});
    addProperty(&counter_);
    counter_.setPropertyName("Wartość zadana");
    counter_.setPlaceholder("1-9999");
    counter_.setRegExp("^\\d{1,4}$");

    address_.setPlaceholder("C##");
    address_.setRegExp("^[Cc](0?\\d|[1-2]\\d|3[01])$");
}

Base *Counter::clone(QQuickItem *parent)
{
    Counter *copyObject = new Counter{parent};
    copyObject->address_ = this->address_;
    copyObject->type_ = this->type_;
    copyObject->counter_ = this->counter_;
    return copyObject;
}

/*!
 * \brief Funkcja rysująca obiekt na ekranie
 */
void Counter::paint(QPainter *painter)
{
    PainterLd painterLd{painter, size()};
    painter->setPen(QPen(Qt::white, 2));
    painterLd.drawCoil();
    painterLd.printCenterLetter('C');
    if(type_ == 0){
        painterLd.printBottomText("Add", -3);
        if(counter_.getTextValue().isEmpty()){
            painterLd.printBottomText("C=0", 6);
        }
        else{
            painterLd.printBottomText("C=" + counter_.getTextValue(), 7);
        }
    }
    else if(type_ == 1) painterLd.printBottomText("Dir");
    else if(type_ == 2) painterLd.printBottomText("Reset");

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

LdProperty::TypeField &Counter::getPropertyType()
{
    return type_;
}

LdProperty::TextField &Counter::getCounter()
{
    return counter_;
}


} //namespace Ld
