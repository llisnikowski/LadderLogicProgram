#include "codeParameter.hpp"
#include "counter.hpp"
#include "text.hpp"
#include "timer.hpp"
#include "weektimer.hpp"

void CodeParameter<Ld::Timer>::set(Ld::Timer &obj)
{
    used = 1;

    auto &timerTime = obj.getTime();
    mode = obj.getPropertyType();
    time = timerTime.getTextValue().toUShort();
    timeUnit = timerTime.getUnits();

    uint32_t timeValue = timerTime.getTextValue().toUShort();
    uint8_t unit = timerTime.getUnits();

    if(unit == 0){  // ms
        if(timeValue <= 9999){
            timeUnit = 's';   //ssmm
        }
        else{
            timeValue /= 100;
            unit = 1;
        }
    }
    if(unit == 1){ //s
        if(timeValue <= 99*60 + 59){
            time = time/60 * 100 + time % 60;
            timeUnit = 'm';   //mmss
        }
        else{
            timeValue /= 60;
            unit = 2;
        }
    }
    if(unit == 2){
        if(time <= 99*60 + 59){
            time = time/60 * 100 + time % 60;
            timeUnit = 'h';   //hhmm
        }
        else{
            timeValue /= 60;
            unit = 3;
        }
    }
    if(unit == 3){
        if(timeValue < 99){
            time = time * 100;
        }
        else{
            time = 9900;
        }
        timeUnit = 'h';   //hhmm
    }
}

QString CodeParameter<Ld::Timer>::get()
{
    if(!used) return "";
    QString parametrCode = QString(timeUnit);
    parametrCode += QString("%1").arg(time, 4, 10, QChar('0'));
    parametrCode += 'm' + QString::number(mode % 10);
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

    auto &textList = obj.getTexts().getTextsList();
    for(int i = 0; i < 4; i++){
        text[i] = textList[i];
    }
}

QString CodeParameter<Ld::Text>::get()
{
    if(!used) return "";
    QString parametrCode;

    for(int i = 0; i < 4; i++){
        parametrCode += text[i];
        if(i < 3) parametrCode += QString(" ");
    }
    parametrCode += "\r\n";
    return parametrCode;
}

