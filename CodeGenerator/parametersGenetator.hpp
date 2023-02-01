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

constexpr uint NUMBER_OF_TIMER {16};
constexpr uint NUMBER_OF_COUNTER {16};
constexpr uint NUMBER_OF_WEEKTIMER {16};
constexpr uint NUMBER_OF_TEXT {99};


class ParametersGenetator : public QObject
{
public:
    ParametersGenetator(QObject *parent = nullptr);

    void setGenerateErrors(GenerateErrors *generateErrors);
    QString getCode();
    void clear();

    template <typename T>
    void checkAndSet(T &obj);

private:
    enum {
        repeating = -1,
        addressFail = -2,
        skip = -3
    };

    template <typename T>
    int check(T &obj);
    template <typename T>
    void set(int addressNr, T &obj);

    template <typename T>
    constexpr int maxNumber();
    template <typename T>
    constexpr CodeParameter<T> *parametersArray();
    template <typename T>
    constexpr QChar getChar();

    template <typename T>
    QString getPrefix(uint nr);
    template <typename T>
    QString get(uint nr);

    CodeParameter <Ld::Timer>timersParametrs_[NUMBER_OF_TIMER];
    CodeParameter <Ld::Counter>countersParametrs_[NUMBER_OF_COUNTER];
    CodeParameter <Ld::Weektimer>weekTimesParametrs_[NUMBER_OF_WEEKTIMER];
    CodeParameter <Ld::Text>textParameters_[NUMBER_OF_TEXT];

    GenerateErrors *generateErrors_;
};


template<typename T>
constexpr int ParametersGenetator::maxNumber()
{
    if constexpr(std::is_same<T, Ld::Timer>::value){
        return NUMBER_OF_TIMER;
    }
    else if constexpr(std::is_same<T, Ld::Counter>::value){
        return NUMBER_OF_COUNTER;
    }
    else if constexpr(std::is_same<T, Ld::Weektimer>::value){
        return NUMBER_OF_WEEKTIMER;
    }
    else if constexpr(std::is_same<T, Ld::Text>::value){
        return NUMBER_OF_TEXT;
    }
}

template<typename T>
constexpr CodeParameter<T> *ParametersGenetator::parametersArray()
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
constexpr QChar ParametersGenetator::getChar()
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
void ParametersGenetator::checkAndSet(T &obj)
{
    int nr = check(obj);
    if(nr >= 0){
        set(nr, obj);
    }
    if(generateErrors_){
        if(nr == repeating){
            generateErrors_->addError("Powtórzony adres obiektu "
                                      + obj.getAddress().getTextValue());
        }
        else if(nr == addressFail){
            generateErrors_->addError("Niepoprawny adres obiektu: "
                                      + obj.getAddress().getTextValue());
        }
    }
}

template<typename T>
int ParametersGenetator::check(T &obj)
{
    auto &address = obj.getAddress();
    if(!address.textIsValid()) return addressFail;
    QString addressText = address.getAddressNr();
    uint addressNr = addressText.toUInt();
    if(addressNr >= maxNumber<T>()) return addressFail;
    if(parametersArray<T>()[addressNr].used == 1){
        if constexpr(std::is_same<T, Ld::Counter>::value){
            if(obj.getPropertyType().getValue() == 0){
                return repeating;
            }
            else{
                return skip;
            }
        }
        else{
            return repeating;
        }
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
