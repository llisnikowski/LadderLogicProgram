#include <stdint.h>
#include <QString>

namespace Ld{
class Timer;
class Counter;
class Weektimer;
class Text;
}

template <typename T>
struct CodeParameter
{
    bool used{};
};

template <>
struct CodeParameter<Ld::Timer>
{
    void set(Ld::Timer &obj);
    QString get();

    bool used{};
    uint8_t mode{};
    uint16_t time{};
    char timeUnit{};
};

template <>
struct CodeParameter<Ld::Counter>
{
    void set(Ld::Counter &obj);
    QString get();

    bool used{};
    uint32_t count{};
};

template <>
struct CodeParameter<Ld::Weektimer>
{
    void set(Ld::Weektimer &obj);
    QString get();

    bool used{};
    uint16_t timeOn{};
    uint16_t timeOff{};
    uint8_t days{};
};

template <>
struct CodeParameter<Ld::Text>
{
    void set(Ld::Text &obj);
    QString get();

    bool used{};
    QString text[4]{};
};




