#include "timeField.hpp"

namespace LdProperty {

TimeField::TimeField(QQuickItem *parent)
    :Base{parent}, textValue_{}, units_{}, model_{}
{
    setPropertyName("Czas");
    setModel({"s:ms*10", "min:s", "h:min"});
}

TimeField &TimeField::operator=(const TimeField &timeField)
{
    if(this != &timeField){
        Base::operator=(timeField);
        setUnits(timeField.units_);
        setTextValue(timeField.textValue_);
        setModel(timeField.model_);
    }
    return *this;
}

void TimeField::setTextValue(QString textValue)
{
    textValue_ = textValue;
    if(validFunction_)
        textIsValid_ = validFunction_(textValue_);
    emit textValueChanged();
}

QString TimeField::getTextValue() const
{
    return textValue_;
}

void TimeField::setPlaceholder(const QString &textValue)
{
    placeholder_ = textValue;
    emit placeholderChanged();
}

void TimeField::setPlaceholder(QString &&textValue)
{
    placeholder_ = textValue;
    emit placeholderChanged();
}

QString TimeField::getPlaceholder() const
{
    return placeholder_;
}

void TimeField::setValidator(std::function<bool(QString &)> fun)
{
    validFunction_ = fun;
}

bool TimeField::textIsValid()
{
    return textIsValid_;
}


void TimeField::setUnits(int units)
{
    units_ = units;
    emit unitsChanged();
}

int TimeField::getUnits() const
{
    return units_;
}

const QStringList &TimeField::getModel() const
{
    return model_;
}

void TimeField::setModel(const QStringList &model)
{
    model_ = model;
    emit modelChanged();
}

void TimeField::setModel(const QStringList &&model)
{
    model_ = model;
    emit modelChanged();
}

} // namespace LdProperty



QDataStream & operator<<(QDataStream &stream, const LdProperty::TimeField &timeField)
{
    stream << static_cast<const LdProperty::Base&>(timeField)
           << timeField.getTextValue() << timeField.getUnits();
    return stream;
}

QDataStream & operator>>(QDataStream &stream, LdProperty::TimeField &timeField)
{
    QString textValue;
    int units;
    stream >> static_cast<LdProperty::Base&>(timeField) >> textValue >> units;
    timeField.setTextValue(textValue);
    timeField.setUnits(units);
    return stream;
}




