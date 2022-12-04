#include "textField.hpp"

namespace LdProperty {

TextField::TextField(QQuickItem *parent)
    :Base{parent}, textValue_{}
{
}

Type TextField::getType() const
{
    return Type::TextField;
}

void TextField::setTextValue(QString textValue)
{
    qDebug() <<"set value: "<< textValue;
    textValue_ = textValue;
    emit textValueChanged();
}

QString TextField::getTextValue()
{
    qDebug() <<"get value: "<< textValue_;
    return textValue_;
}

QByteArray TextField::getData() const
{
    QByteArray itemData;
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);
    dataStream << QString("LdProperty") << static_cast<int>(getType());
    return itemData;
}





} // namespace LdProperty
