#include "weektimer.hpp"
#include <QPainter>
#include "painterLd.hpp"
#include <QRegularExpression>

namespace Ld {

Weektimer::Weektimer(QQuickItem *parent)
    :Input{parent}, timeOn_{this}, timeOff_{this}, daysOfWeek_{this}
{
    addProperty(&timeOn_);
    timeOn_.setPropertyName("Czas włączenia");
    addProperty(&timeOff_);
    timeOff_.setPropertyName("Czas wyłączenia");
    addProperty(&daysOfWeek_);

    timeOn_.setPlaceholder("HH:MM");
    timeOff_.setPlaceholder("HH:MM");

    timeOn_.setRegExp("^([0-1]?[0-9]|2[0-3]):[0-5][0-9]$");
    timeOff_.setRegExp("^([0-1]?[0-9]|2[0-3]):[0-5][0-9]$");

    address_.setPlaceholder("Z[00-15]");
    address_.setRegExp("^[Zz]((0?\\d)|(1[0-5]))$");
}

Base *Weektimer::clone(QQuickItem *parent)
{
    Weektimer *copyObject = new Weektimer{parent};
    copyObject->address_ = this->address_;
    copyObject->timeOn_ = this->timeOn_;
    copyObject->timeOff_ = this->timeOff_;
    copyObject->daysOfWeek_ = this->daysOfWeek_;
    return copyObject;
}

void Weektimer::paint(QPainter *painter)
{
    PainterLd painterLd{painter, size()};
    painter->setPen(QPen(Qt::white, 2));
    painterLd.drawContact();
    painterLd.printCenterLetter('Z');

    if(selected_){
        painter->setPen(QPen(Qt::black, 2));
        painterLd.drawFrame();
    }
}

Type Weektimer::getType() const
{
    return Type::Weektimer;
}

QByteArray Weektimer::getData() const
{
    QByteArray itemData;
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);
    dataStream << QString("Ld") << static_cast<int>(getType()) << address_
               << timeOn_ << timeOff_ << daysOfWeek_;
    return itemData;
}


} //namespace Ld
