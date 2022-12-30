#include "parametersArray.hpp"
#include "timer.hpp"

ParametersArray::ParametersArray(QObject *parent)
    :QObject{parent}, timersParametrs_{}, countersParametrs_{},
    weekTimesParametrs_{}, textParameters_{}
{

}

void ParametersArray::get(QString &out)
{
    for(int i = 0; i < SINGLE_TYPE_PARAMETER_COUNT; i++){
        get(i, timersParametrs_[i], out);
    }
}

ParametrStatus ParametersArray::set(Ld::Timer &obj)
{
    auto &address = obj.getAddress();
    if(!address.textIsValid()) return ParametrStatus::incorrectValue;
    QString addressText = address.getAddressNr();
    uint addressNr = addressText.toUInt();
    if(addressNr >= SINGLE_TYPE_PARAMETER_COUNT) return ParametrStatus::incorrectValue;
    if(timersParametrs_[addressNr].used == 1) return ParametrStatus::repeatedAddress;
    timersParametrs_[addressNr].used = 1;

    auto &time = obj.getTime();
    timersParametrs_[addressNr].mode = obj.getPropertyType();
    timersParametrs_[addressNr].time = time.getTextValue().toUShort();
    timersParametrs_[addressNr].timeUnit = time.getUnits();

    uint32_t timeValue = time.getTextValue().toUShort();
    uint8_t unit = time.getUnits();

    if(unit == 0){  // ms
        if(timeValue <= 9999){
            timersParametrs_[addressNr].time = time;   //accuracy = 10ms
            timersParametrs_[addressNr].timeUnit = 's';   //ssmm
        }
        else{
            timeValue /= 100;
            unit = 1;
        }
    }
    if(unit == 1){ //s
        if(timeValue <= 99*60 + 59){
            timersParametrs_[addressNr].time = time/60 * 100 + time % 60;
            timersParametrs_[addressNr].timeUnit = 'm';   //mmss
        }
        else{
            timeValue /= 60;
            unit = 2;
        }
    }
    if(unit == 2){
        if(time <= 99*60 + 59){
            timersParametrs_[addressNr].time = time/60 * 100 + time % 60;
            timersParametrs_[addressNr].timeUnit = 'h';   //hhmm
        }
        else{
            timeValue /= 60;
            unit = 3;
        }
    }
    if(unit == 3){
        if(timeValue < 99){
            timersParametrs_[addressNr].time = time * 100;
        }
        else{
            timersParametrs_[addressNr].time = 9900;
        }
        timersParametrs_[addressNr].timeUnit = 'h';   //hhmm
    }

    return ParametrStatus::correctValue;
}

ParametrStatus ParametersArray::set(Ld::Counter &obj)
{
    return ParametrStatus::correctValue;
}

ParametrStatus ParametersArray::set(Ld::Weektimer &obj)
{
    return ParametrStatus::correctValue;
}

ParametrStatus ParametersArray::set(Ld::Text &obj)
{
    return ParametrStatus::correctValue;
}

void ParametersArray::get(uint nr, TimersParameter &timer, QString &out)
{
    if(!timer.used) return;
    QString parametrCode = QString(":T") + (nr < 10 ? "0" : "") +
                           QString::number(nr%100) + " ";
    parametrCode += timer.timeUnit;
    uint16_t time = timer.time;
    parametrCode += QString::number((time / 1000)%10) + QString::number((time / 100)%10)
                    + QString::number((time / 10)%10) + QString::number((time / 1)%10);

    parametrCode += 'm' + QString::number(timer.mode % 10);
    parametrCode += "\r\n";
    out += parametrCode;
}
