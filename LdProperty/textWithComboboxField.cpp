#include "textWithComboboxField.hpp"

namespace LdProperty {

TextWithComboboxField::TextWithComboboxField(QQuickItem *parent)
    :TextField{parent}, units_{}, model_{}
{
}

TextWithComboboxField &TextWithComboboxField::operator=(const TextWithComboboxField &obj)
{
    if(this != &obj){
        TextField::operator=(obj);
        setUnits(obj.units_);
        setTextValue(obj.textValue_);
        setModel(obj.model_);
    }
    return *this;
}



void TextWithComboboxField::setUnits(int units)
{
    units_ = units;
    emit unitsChanged();
}

int TextWithComboboxField::getUnits() const
{
    return units_;
}

const QStringList &TextWithComboboxField::getModel() const
{
    return model_;
}

void TextWithComboboxField::setModel(const QStringList &model)
{
    model_ = model;
    emit modelChanged();
}

void TextWithComboboxField::setModel(const QStringList &&model)
{
    model_ = model;
    emit modelChanged();
}

} // namespace LdProperty



QDataStream & operator<<(QDataStream &stream, const LdProperty::TextWithComboboxField &obj)
{
    stream << static_cast<const LdProperty::TextField&>(obj)
           << obj.getUnits();
    return stream;
}

QDataStream & operator>>(QDataStream &stream, LdProperty::TextWithComboboxField &obj)
{
    int units;
    stream >> static_cast<LdProperty::TextField&>(obj) >> units;
    obj.setUnits(units);
    return stream;
}




