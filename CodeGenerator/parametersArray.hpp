#ifndef PARAMETERSARRAY_HPP
#define PARAMETERSARRAY_HPP

#include <QObject>
#include <stdint.h>



namespace Ld{
class Timer;
class Counter;
class Weektimer;
class Text;
}

struct TimersParameter
{
    bool used{};
    uint8_t mode{};
    uint16_t time{};
    char timeUnit{};
};
struct CountersParameter
{
    bool used{};
    uint32_t count{};
};
struct WeektimesParameter
{
    bool used{};
    uint16_t timeOn{};
    uint16_t timeOff{};
    uint8_t days{};
};
struct TextParameter
{
    bool used{};
    QString text[4]{};
};


enum class ParametrStatus{
    correctValue,
    repeatedAddress,
    incorrectValue
};

constexpr uint SINGLE_TYPE_PARAMETER_COUNT {16};

class ParametersArray : public QObject
{
public:
    ParametersArray(QObject *parent = nullptr);

    void getCode(QString &out);
    void clear();

    ParametrStatus set(Ld::Timer &obj);
    ParametrStatus set(Ld::Counter &obj);
    ParametrStatus set(Ld::Weektimer &obj);
    ParametrStatus set(Ld::Text &obj);

private:
    void get(uint nr, TimersParameter &timer, QString &out);
    void get(uint nr, CountersParameter &counter, QString &out);
    void get(uint nr, WeektimesParameter &weektimer, QString &out);
    void get(uint nr, TextParameter &text, QString &out);

    TimersParameter timersParametrs_[SINGLE_TYPE_PARAMETER_COUNT];
    CountersParameter countersParametrs_[SINGLE_TYPE_PARAMETER_COUNT];
    WeektimesParameter weekTimesParametrs_[SINGLE_TYPE_PARAMETER_COUNT];
    TextParameter textParameters_[SINGLE_TYPE_PARAMETER_COUNT];
};

#endif // PARAMETERS_HPP
