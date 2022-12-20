#include "textField.hpp"
#include <QQmlEngine>

namespace LdProperty {

TextField::TextField(QQuickItem *parent)
    :Base{parent}, textValue_{}
{
}

TextField &TextField::operator=(const TextField &textField)
{
    if(this != &textField){
        Base::operator=(textField);
        setTextValue(textField.textValue_);
    }
    return *this;
}

void TextField::setTextValue(QString textValue)
{
    textValue_ = textValue;
    emit textValueChanged();
}

QString TextField::getTextValue() const
{
    return textValue_;
}


} // namespace LdProperty



QDataStream & operator<<(QDataStream &stream, const LdProperty::TextField &textField)
{
    stream << static_cast<const LdProperty::Base&>(textField) << textField.getTextValue();
    return stream;
}

QDataStream & operator>>(QDataStream &stream, LdProperty::TextField &textField)
{
    QString value;
    stream >> static_cast<LdProperty::Base&>(textField) >> value;
    textField.setTextValue(value);
    return stream;
}


