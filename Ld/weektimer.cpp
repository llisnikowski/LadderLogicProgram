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

    timeOn_.setPlaceholder("[0-23]:[00-59]");
    timeOff_.setPlaceholder("[0-23]:[00-59]");

    auto validTimeFun = [](QString &text)->bool{
        QStringList textList = text.split(':');
        if(textList.count() < 2){
            text = text.remove(QRegularExpression{"[^\\d]"});
            return false;
        }
        textList[0] = textList[0].remove(QRegularExpression{"[^\\d{0,2}]"});
        textList[1] = textList[1].remove(QRegularExpression{"[^\\d{0,2}]"});
        text = textList[0] + ":" + textList[1];
        int textInt0 = textList[0].toInt();
        int textInt1 = textList[1].toInt();
        if(textInt0 < 0 || textInt0 >= 24) return false;
        if(textInt1 < 0 || textInt1 >= 60) return false;
        return true;
    };

    timeOn_.setValidator(validTimeFun);
    timeOff_.setValidator(validTimeFun);


    address_.setPlaceholder("Z[00-15]");
    address_.setValidator([](QString &text)->bool{
        text = text.toUpper();
        QRegularExpression regExp{"^[Z]((0?\\d)|(1[0-5]))$"};
        return regExp.match(text).hasMatch();
    });
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
