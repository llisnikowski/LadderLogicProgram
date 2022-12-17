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

void TextField::setVisible(bool visible)
{
    if(qmlObject_){
        delete qmlObject_;
        qmlObject_ = nullptr;
    }

    if(!visible) return;
    if(QCoreApplication::startingUp()) return;

    QQmlEngine *engine = new QQmlEngine{this};
    QQmlComponent component(engine, QUrl(QStringLiteral("qrc:/LdProperty_textField.qml")),
                            QQmlComponent::PreferSynchronous, this);
    QVariantMap qvMap{{"rootModel", QVariant::fromValue(this)}};
    qmlObject_ = qobject_cast<QQuickItem *>(component.createWithInitialProperties(qvMap));
    if(qmlObject_){
        qmlObject_->setParentItem(this);
        QObject::connect(qmlObject_, &QQuickItem::focusChanged,
                         this, &TextField::itemFocus);
    }
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


