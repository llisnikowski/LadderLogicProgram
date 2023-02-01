#include "parametersGenetator.hpp"
#include "counter.hpp"
#include "text.hpp"
#include "timer.hpp"
#include "weektimer.hpp"

ParametersGenetator::ParametersGenetator(QObject *parent)
    :QObject{parent}, timersParametrs_{}, countersParametrs_{},
    weekTimesParametrs_{}, textParameters_{}, generateErrors_{}
{

}

void ParametersGenetator::setGenerateErrors(GenerateErrors *generateErrors)
{
    generateErrors_ = generateErrors;
}

QString ParametersGenetator::getCode()
{
    QString code;
    for(int i = 0; i < NUMBER_OF_TIMER; i++){
        code += get<Ld::Timer>(i);
    }
    for(int i = 0; i < NUMBER_OF_COUNTER; i++){
        code += get<Ld::Counter>(i);
    }
    for(int i = 0; i < NUMBER_OF_WEEKTIMER; i++){
        code += get<Ld::Weektimer>(i);
    }
    for(int i = 0; i < NUMBER_OF_TEXT; i++){
        code += get<Ld::Text>(i);
    }
    return code;
}

void ParametersGenetator::clear()
{
    for(int i = 0; i < NUMBER_OF_TIMER; i++){
        timersParametrs_[i].used = 0;
    }
    for(int i = 0; i < NUMBER_OF_COUNTER; i++){
        countersParametrs_[i].used = 0;
    }
    for(int i = 0; i < NUMBER_OF_WEEKTIMER; i++){
        weekTimesParametrs_[i].used = 0;
    }
    for(int i = 0; i < NUMBER_OF_TEXT; i++){
        textParameters_[i].used = 0;
    }
}













