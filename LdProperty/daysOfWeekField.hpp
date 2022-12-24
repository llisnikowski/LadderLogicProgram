#ifndef WEEKFIELD_HPP
#define WEEKFIELD_HPP

#include "LdProperty/base.hpp"

namespace LdProperty {

class DaysOfWeekField : public Base
{
    Q_OBJECT
    Q_PROPERTY(uint8_t value READ getValue WRITE setValue NOTIFY valueChanged)
public:
    DaysOfWeekField(QQuickItem *parent = nullptr);
    DaysOfWeekField &operator=(const DaysOfWeekField &daysOfWeekField);

    void setValue(uint8_t value);
    uint8_t getValue() const;
    void operator=(int value);
    operator int();


public slots:
    bool getDay(uint8_t day);
    void setDay(uint8_t day);
    void resetDay(uint8_t day);

signals:
    void valueChanged();

protected:
    uint8_t value_;
};

} // namespace LdProperty


QDataStream &operator<<(QDataStream &stream, const LdProperty::DaysOfWeekField &daysOfWeekField);
QDataStream & operator>>(QDataStream &stream, LdProperty::DaysOfWeekField &daysOfWeekField);

#endif // WEEKFIELD_HPP
