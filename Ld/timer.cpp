#include "timer.hpp"
#include <QPainter>
#include "painterLd.hpp"
#include "type.hpp"
#include <QRegularExpression>

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

    address_.setPlaceholder("Txx");
    address_.setRegExp("^[Tt]((0?\\d)|(1[0-5]))$");

    time_.setPropertyName("Czas");
    time_.setPlaceholder("1-10000");
    time_.setModel({"10ms", "s", "min", "h"});
    time_.setRegExp("^\\d{0,6}$");
    connect(&time_, &LdProperty::TextWithComboboxField::unitsChanged, this, [this](){
        int units = time_.getUnits();
        switch (units)
        {
        case 0:
            time_.setPlaceholder("1-10000");
            break;
        case 1:
            time_.setPlaceholder("1-6000");
            break;
        case 2:
            time_.setPlaceholder("1-6000");
            break;
        case 3:
            time_.setPlaceholder("1-100");
            break;
        }

    });
//    time_.setValidator([](QString &text)->bool{
//        QStringList textList = text.split(':');
//        if(textList.count() < 2){
//            text = text.remove(QRegularExpression{"[^\\d]"});
//            return false;
//        }
//        textList[0] = textList[0].remove(QRegularExpression{"[^\\d{0,2}]"});
//        textList[1] = textList[1].remove(QRegularExpression{"[^\\d{0,2}]"});
//        text = textList[0] + ":" + textList[1];
//        int textInt0 = textList[0].toInt();
//        int textInt1 = textList[1].toInt();
//        if(textInt0 < 0 || textInt0 > 99) return false;
//        if(textInt1 < 0 || textInt1 > 99) return false;
//        return true;
//    });
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
