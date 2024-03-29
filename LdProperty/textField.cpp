#include "textField.hpp"
#include <QQmlEngine>
#include <QRegularExpression>

namespace LdProperty {

TextField::TextField(QQuickItem *parent)
    :Base{parent}, textValue_{}, textIsValid_{true}, regExpValidator_{}
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

void TextField::operator=(QString value)
{
    setTextValue(value);
}

TextField::operator QString()
{
    return getTextValue();
}

void TextField::operator=(int value)
{
    setTextValue(QString::number(value));
}

TextField::operator int()
{
    return textValue_.remove(QRegularExpression{"[^\\d\\$]"}).toInt();
}


void TextField::setPlaceholder(const QString &textValue)
{
    placeholder_ = textValue;
    emit placeholderChanged();
}

void TextField::setPlaceholder(QString &&textValue)
{
    placeholder_ = textValue;
    emit placeholderChanged();
}

QString TextField::getPlaceholder() const
{
    return placeholder_;
}

bool TextField::textIsValid()
{
    int offset = 0;
    QValidator::State state = regExpValidator_.validate(textValue_, offset);
    return state == QValidator::Acceptable;
}

QObject *TextField::getRegExp()
{
    return &regExpValidator_;
}

void TextField::setRegExp(QString &&getRegExp)
{
    regExpValidator_.setRegularExpression(QRegularExpression{getRegExp});
    emit regExpChanged();
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


