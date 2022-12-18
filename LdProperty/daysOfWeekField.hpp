#ifndef WEEKFIELD_HPP
#define WEEKFIELD_HPP

#include "LdProperty/base.hpp"

namespace LdProperty {

class DaysOfWeekField : public Base
{
    Q_OBJECT
    Q_PROPERTY(int value READ getValue WRITE setValue NOTIFY valueChanged)
public:
    DaysOfWeekField(QQuickItem *parent = nullptr);
    DaysOfWeekField &operator=(const DaysOfWeekField &daysOfWeekField);

    void setValue(int value);
    int getValue() const;

public slots:
    bool getDay(int day);
    void setDay(int day);
    void resetDay(int day);

signals:
    void valueChanged();

protected:
    int value_;
};

} // namespace LdProperty


QDataStream &operator<<(QDataStream &stream, const LdProperty::DaysOfWeekField &daysOfWeekField);
QDataStream & operator>>(QDataStream &stream, LdProperty::DaysOfWeekField &daysOfWeekField);

#endif // WEEKFIELD_HPP
