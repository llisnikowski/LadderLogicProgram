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

void DaysOfWeekField::setValue(int value)
{
    value_ = value;
    emit valueChanged();
}

int DaysOfWeekField::getValue() const
{
    return value_;
}

bool DaysOfWeekField::getDay(int day)
{
    return value_ & (1 << day);
}

void DaysOfWeekField::setDay(int day)
{
    value_ |= (1<<day);
}

void DaysOfWeekField::resetDay(int day)
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
