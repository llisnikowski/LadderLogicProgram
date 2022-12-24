#include "comboboxField.hpp"
#include <QQmlEngine>

namespace LdProperty {

ComboboxField::ComboboxField(QQuickItem *parent)
    :Base{parent}, value_{}, model_{}
{
}

ComboboxField &ComboboxField::operator=(const ComboboxField &comboboxField)
{
    if(this != &comboboxField){
        Base::operator=(comboboxField);
        setValue(comboboxField.value_);
        setModel(comboboxField.model_);
    }
    return *this;
}

void ComboboxField::setValue(int value)
{
    value_ = value;
    emit valueChanged();
}

int ComboboxField::getValue() const
{
    return value_;
}

void ComboboxField::operator=(int value)
{
    setValue(value);
}

ComboboxField::operator int()
{
    return getValue();
}

const QStringList &ComboboxField::getModel() const
{
    return model_;
}

void ComboboxField::setModel(const QStringList &model)
{
    model_ = model;
    emit modelChanged();
}

void ComboboxField::setModel(const QStringList &&model)
{
    model_ = model;
    emit modelChanged();
}


} // namespace LdProperty




QDataStream & operator<<(QDataStream &stream, const LdProperty::ComboboxField &comboboxField)
{
    stream << static_cast<const LdProperty::Base&>(comboboxField) << comboboxField.getValue();
    return stream;
}

QDataStream & operator>>(QDataStream &stream, LdProperty::ComboboxField &comboboxField)
{
    int value;
    stream >> static_cast<LdProperty::Base&>(comboboxField) >> value;
    comboboxField.setValue(value);
    return stream;
}




