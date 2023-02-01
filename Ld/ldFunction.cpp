#include "ldFunction.hpp"
#include <QString>
#include "line.hpp"
#include "coil.hpp"
#include "timer.hpp"
#include "counter.hpp"
#include "contact.hpp"
#include "weektimer.hpp"
#include "text.hpp"
#include "node.hpp"
#include "type.hpp"
#include "drag.hpp"

QDataStream & operator >>(QDataStream & stream, Ld::Base **ld)
{
    QString title;
    int type;
    stream >> title >> type;
    if(title != "Ld"){
        stream.setStatus(QDataStream::ReadCorruptData);
        return stream;
    }
    switch(type)
    {
    case static_cast<int>(Ld::Type::Contact):
    {
        auto contact = new Ld::Contact;
        stream >> contact->address_ >> contact->type_;
        *ld = contact;
        break;
    }
    case static_cast<int>(Ld::Type::Weektimer):
    {
        auto weektimer = new Ld::Weektimer;
        stream >> weektimer->address_ >> weektimer->timeOn_
            >> weektimer->timeOff_ >> weektimer->daysOfWeek_;
        *ld = weektimer;
        break;
    }
    case static_cast<int>(Ld::Type::Coil):
    {
        auto coil = new Ld::Coil;
        stream >> coil->address_ >> coil->type_;
        *ld = coil;
        break;
    }
    case static_cast<int>(Ld::Type::Timer):
    {
        auto timer = new Ld::Timer;
        stream >> timer->address_;
        stream >> timer->timeCourse_;
        stream >> timer->timeMode_;
        stream >> timer->times_[0];
        stream >> timer->times_[1];
        stream >> timer->waveforms_;
        *ld = timer;
        break;
    }
    case static_cast<int>(Ld::Type::Counter):
    {
        auto counter = new Ld::Counter;
        stream >> counter->address_ >> counter->type_ >> counter->counter_;
        *ld = counter;
        break;
    }
    case static_cast<int>(Ld::Type::Text):
    {
        auto text = new Ld::Text;
        stream >> text->address_ >> text->line_ >> text->text_ >> text->displayParametr_;
        *ld = text;
        break;
    }
    case static_cast<int>(Ld::Type::Line):
        *ld = new Ld::Line;
        break;
    case static_cast<int>(Ld::Type::Node):
        *ld = new Ld::Node;
        break;
    }

    return stream;
}

Ld::Base * getLdObject(const QByteArray &dataArray)
{
    Ld::Base * ldObj{};
    QDataStream dataStream(dataArray);
    dataStream >> &ldObj;
    return ldObj;
}

