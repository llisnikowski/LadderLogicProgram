#include "parametersArray.hpp"

ParametersArray::ParametersArray(QObject *parent)
    :QObject{parent}, timersParametrs_{}, countersParametrs_{},
    weekTimesParametrs_{}, textParameters_{}
{

}

ParametrStatus ParametersArray::set(Ld::Timer &obj)
{
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
