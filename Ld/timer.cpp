#include "timer.hpp"
#include <QPainter>
#include "painterLd.hpp"
#include "type.hpp"
#include <QRegularExpression>

namespace Ld {

Timer::Timer(QQuickItem *parent)
    :Output{parent}, timeCourse_{this}, timeMode_{this}, times_{{this},{this}},
    waveforms_{this}
{
    address_.setPlaceholder("T##");
    address_.setRegExp("^[Tt](0?\\d|[1-2]\\d|3[01])$");

    addProperty(&timeCourse_);
    timeCourse_.setModel({"Imp1", "Imp2", "Ton", "Tof", "Imp3", "Tof2", "Gen"});
    QObject::connect(&timeCourse_, &LdProperty::ComboboxField::valueChanged,
                     this, &QQuickItem::update);
    QObject::connect(&timeCourse_, &LdProperty::ComboboxField::itemFocus,
                     this, [this](bool focus){if(focus) emit clicked();});

    QObject::connect(&timeMode_, &LdProperty::ComboboxField::valueChanged,
                     this, &QQuickItem::update);
    QObject::connect(&times_[0], &LdProperty::TextField::textValueChanged,
                     this, &QQuickItem::update);
    QObject::connect(&times_[1], &LdProperty::TextField::textValueChanged,
                     this, &QQuickItem::update);

    addProperty(&waveforms_);
    waveforms_.setUrl(QUrl("qrc:/img/timer/timer1.png"));

    addProperty(&timeMode_);
    timeMode_.setPropertyName("Czas");
    timeMode_.setModel({"s:ms", "min:s", "h:s"});

    addProperty(&times_[0]);
    times_[0].setPropertyName("s");
    times_[0].setPlaceholder("0-99");
    times_[0].setRegExp("^\\d{0,2}$");

    addProperty(&times_[1]);
    times_[1].setPropertyName("10ms");
    times_[1].setPlaceholder("0-99");
    times_[1].setRegExp("^\\d{0,2}$");

    connect(&timeMode_, &LdProperty::ComboboxField::valueChanged, this, [this](){
        switch (timeMode_.getValue())
        {
        case 0:
            times_[0].setPropertyName("s");
            times_[1].setPropertyName("10ms");
            break;
        case 1:
            times_[0].setPropertyName("min");
            times_[1].setPropertyName("s");
            break;
        default:
            times_[0].setPropertyName("h");
            times_[1].setPropertyName("min");
            break;
        }

    });

    QObject::connect(&timeCourse_, &LdProperty::ComboboxField::valueChanged,
                     this, [this](){
                         waveforms_.setUrl(QUrl(
                             QString("img/timer/timer%1.png").arg(timeCourse_.getValue()+1)));
                     });

}

Base *Timer::clone(QQuickItem *parent)
{
    Timer *copyObject = new Timer{parent};
    copyObject->address_ = this->address_;
    copyObject->timeCourse_ = this->timeCourse_;
    copyObject->timeMode_ = this->timeMode_;
    copyObject->times_[0] = this->times_[0];
    copyObject->times_[1] = this->times_[1];
    copyObject->waveforms_ = this->waveforms_;
    return copyObject;
}

/*!
 * \brief Funkcja rysująca obiekt na ekranie
 */
void Timer::paintBase(QPainter *painter)
{
    PainterLd painterLd{painter, size()};
    painter->setPen(QPen(Qt::white, 2));
    painterLd.drawCoil();
    painterLd.printCenterLetter('T');
}

void Timer::paintAdditions(QPainter *painter)
{
    PainterLd painterLd{painter, size()};
    int czas[2] = {times_[0], times_[1]};
    QString timeText;
    switch (timeMode_.getValue())
    {
    case 0:
        timeText = QString("T=%1.%2s")
                       .arg(czas[0], 1, 10, QChar('0'))
                       .arg(czas[1], 2, 10, QChar('0'));

        break;
    case 1:
        timeText = QString("T=%1:%2m")
                       .arg(czas[0], 1, 10, QChar('0'))
                       .arg(czas[1], 2, 10, QChar('0'));
        break;
    default:
        timeText = QString("T=%1:%2h")
                       .arg(czas[0], 1, 10, QChar('0'))
                       .arg(czas[1], 2, 10, QChar('0'));
        break;
    }
    painterLd.printBottomText(timeText);
    Drag::paintAdditions(painter);
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
               << timeCourse_ << timeMode_ << times_[0] << times_[1]
               << waveforms_;
    return itemData;
}

LdProperty::TypeField &Timer::getTimeCourse()
{
    return timeCourse_;
}

LdProperty::ComboboxField &Timer::getTimeMode()
{
    return timeMode_;
}

LdProperty::TextField &Timer::getTime(int i)
{
    if(i==0) return times_[0];
    return times_[1];
}



} //namespace Ld
