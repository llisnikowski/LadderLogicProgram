#ifndef PARAMETERSGENERATOR_HPP
#define PARAMETERSGENERATOR_HPP

#include <QObject>
#include <stdint.h>
#include "generateErrors.hpp"
#include "codeParameter.hpp"

namespace Ld{
class Timer;
class Counter;
class Weektimer;
class Text;
}

constexpr uint SINGLE_TYPE_PARAMETER_COUNT {16};

class ParametersGenetator : public QObject
{
public:
    ParametersGenetator(QObject *parent = nullptr);

    void setGenerateErrors(GenerateErrors *generateErrors);
    QString getCode();
    void clear();

    template <typename T>
    void checkAndSet(T &obj, int network=-1);

private:
    template <typename T>
    int check(T &obj);
    template <typename T>
    void set(int addressNr, T &obj);

    template <typename T>
    CodeParameter<T> *parametersArray();
    template <typename T>
    QChar getChar();

    template <typename T>
    QString getPrefix(uint nr);
    template <typename T>
    QString get(uint nr);

    CodeParameter <Ld::Timer>timersParametrs_[SINGLE_TYPE_PARAMETER_COUNT];
    CodeParameter <Ld::Counter>countersParametrs_[SINGLE_TYPE_PARAMETER_COUNT];
    CodeParameter <Ld::Weektimer>weekTimesParametrs_[SINGLE_TYPE_PARAMETER_COUNT];
    CodeParameter <Ld::Text>textParameters_[SINGLE_TYPE_PARAMETER_COUNT];

    GenerateErrors *generateErrors_;
};



template<typename T>
CodeParameter<T> *ParametersGenetator::parametersArray()
{
    if constexpr(std::is_same<T, Ld::Timer>::value){
        return timersParametrs_;
    }
    else if constexpr(std::is_same<T, Ld::Counter>::value){
        return countersParametrs_;
    }
    else if constexpr(std::is_same<T, Ld::Weektimer>::value){
        return weekTimesParametrs_;
    }
    else if constexpr(std::is_same<T, Ld::Text>::value){
        return textParameters_;
    }
}

template<typename T>
QChar ParametersGenetator::getChar()
{
    if constexpr(std::is_same<T, Ld::Timer>::value){
        return 'T';
    }
    else if constexpr(std::is_same<T, Ld::Counter>::value){
        return 'C';
    }
    else if constexpr(std::is_same<T, Ld::Weektimer>::value){
        return 'Z';
    }
    else if constexpr(std::is_same<T, Ld::Text>::value){
        return 'X';
    }
    return ' ';
}

template <typename T>
void ParametersGenetator::checkAndSet(T &obj, int network)
{
    int nr = check(obj);
    if(nr == -1) return;
    set(nr, obj);
}

template<typename T>
int ParametersGenetator::check(T &obj)
{
    auto &address = obj.getAddress();
    if(!address.textIsValid()) return -1;
    QString addressText = address.getAddressNr();
    uint addressNr = addressText.toUInt();
    if(addressNr >= SINGLE_TYPE_PARAMETER_COUNT) return -1;
    if(parametersArray<T>()[addressNr].used == 1){
        return -1;
    }
    return addressNr;
}

template <typename T>
void ParametersGenetator::set(int addressNr, T &obj)
{
    parametersArray<T>()[addressNr].set(obj);
}

template <typename T>
QString ParametersGenetator::getPrefix(uint nr)
{
    return QString(":") + getChar<T>()
           + QString("%1 ").arg(nr, 2, 10, QChar('0'));
}

template<typename T>
QString ParametersGenetator::get(uint nr)
{
    if(!parametersArray<T>()[nr].used) return QString();
    return getPrefix<T>(nr) + parametersArray<T>()[nr].get();
}




#endif // PARAMETERS_HPP
