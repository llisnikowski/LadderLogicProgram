#include "daysOfWeekField.hpp"

namespace LdProperty {

DaysOfWeekField::DaysOfWeekField(QQuickItem *parent)
    :Base{parent}, value_{}
{
    setPropertyName("Dni tygodnia");
}

DaysOfWeekField &DaysOfWeekField::operator=(const DaysOfWeekField &daysOfWeekField)
{
    if(this != &daysOfWeekField){
        Base::operator=(daysOfWeekField);
        setValue(daysOfWeekField.value_);
    }
    return *this;
}

void DaysOfWeekField::setValue(uint8_t value)
{
    value_ = value;
    emit valueChanged();
}

uint8_t DaysOfWeekField::getValue() const
{
    return value_;
}

void DaysOfWeekField::operator=(int value)
{
    setValue(value);
}

DaysOfWeekField::operator int()
{
    return getValue();
}


bool DaysOfWeekField::getDay(uint8_t day)
{
    return value_ & (1 << day);
}

void DaysOfWeekField::setDay(uint8_t day)
{
    value_ |= (1<<day);
}

void DaysOfWeekField::resetDay(uint8_t day)
{
    value_ &= ~(1<<day);
}

} // namespace LdProperty


QDataStream & operator<<(QDataStream &stream, const LdProperty::DaysOfWeekField &daysOfWeekField)
{
    stream << static_cast<const LdProperty::Base&>(daysOfWeekField) << daysOfWeekField.getValue();
    return stream;
}

QDataStream & operator>>(QDataStream &stream, LdProperty::DaysOfWeekField &daysOfWeekField)
{
    int value;
    stream >> static_cast<LdProperty::Base&>(daysOfWeekField) >> value;
    daysOfWeekField.setValue(value);
    return stream;
}
