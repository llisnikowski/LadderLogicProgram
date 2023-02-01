#include "codeParameter.hpp"
#include "counter.hpp"
#include "text.hpp"
#include "timer.hpp"
#include "weektimer.hpp"

void CodeParameter<Ld::Timer>::set(Ld::Timer &obj)
{
    used = 1;

    timeCourse = obj.getTimeCourse().getValue();

    switch (obj.getTimeMode()){
    case 0:
        timeUnit = 's';
        break;
    case 1:
        timeUnit = 'm';
        break;
    case 2:
        timeUnit = 'h';
        break;
    }

    time[0] = obj.getTime(0).getTextValue().toInt() % 100;
    time[1] = obj.getTime(1).getTextValue().toInt() % 100;
}

QString CodeParameter<Ld::Timer>::get()
{
    if(!used) return "";
    QString parametrCode = QString(timeUnit);
    parametrCode += QString("%1").arg(time[0], 2, 10, QChar('0'));
    parametrCode += QString("%1").arg(time[1], 2, 10, QChar('0'));
    parametrCode += 'm' + QString::number(timeCourse % 10);
    parametrCode += "\r\n";
    return parametrCode;
}

void CodeParameter<Ld::Counter>::set(Ld::Counter &obj)
{
    used = 1;

    auto &counter = obj.getCounter();
    count = counter.getTextValue().toUInt() % 10'000;
}

QString CodeParameter<Ld::Counter>::get()
{
    if(!used) return "";
    QString parametrCode = QString("%1").arg(count, 4, 10, QChar('0'));
    parametrCode += "\r\n";
    return parametrCode;
}

void CodeParameter<Ld::Weektimer>::set(Ld::Weektimer &obj)
{
    used = 1;

    QString timeOnText = obj.getTimeOn().getTextValue();
    erase(timeOnText,':');
    timeOn = timeOnText.toShort() % 10000;

    QString timeOffText = obj.getTimeOff().getTextValue();
    erase(timeOffText,':');
    timeOff = timeOffText.toShort() % 10000;

    days = obj.getDaysOfWeek().getValue();
}

QString CodeParameter<Ld::Weektimer>::get()
{
    if(!used) return "";
    QString parametrCode;
    parametrCode += QString("%1 ").arg(timeOn, 4, 10, QChar('0'));
    parametrCode += QString("%1 ").arg(timeOff, 4, 10, QChar('0'));
    parametrCode += QString("%1").arg(days, 8, 2, QChar('0'));
    parametrCode += "\r\n";
    return parametrCode;
}

void CodeParameter<Ld::Text>::set(Ld::Text &obj)
{
    used = 1;
    line = obj.getLine().getValue() % 8;
    text = obj.getText().getTextValue();
    auto &displayParametr = obj.getDisplayParametr();
    if(displayParametr.textIsValid()){
        auto rawText = displayParametr.getTextValue();
        parametr = rawText[0].toUpper();
        if(rawText.length() <= 1){
            parametr += "00";
        }
        else if(rawText.length() == 2){
            parametr +=  QString("0") + rawText[1];
        }
        else{
            parametr += QString(rawText[1]) + rawText[2];
        }
    }
    else{
        parametr = "";
    }
}

QString CodeParameter<Ld::Text>::get()
{
    if(!used) return "";
    QString parametrCode;
    parametrCode += QString::number(line) + ",";
    parametrCode += text + ",";
    parametrCode += parametr;
    parametrCode += "\r\n";
    return parametrCode;
}

