#include "comboboxField.hpp"
#include <QQmlEngine>

namespace LdProperty {

ComboboxField::ComboboxField(QQuickItem *parent)
    :Base{parent}, value_{}, model_{}
{
    setPropertyName("Typ");
}

ComboboxField &ComboboxField::operator=(const ComboboxField &comboboxField)
{
    if(this != &comboboxField){
        Base::operator=(comboboxField);
        setValue(comboboxField.value_);
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

const QStringList &ComboboxField::getModel() const
{
    return model_;
}

void ComboboxField::setModel(QStringList &model)
{
    model_ = model;
    emit modelChanged();
}

void ComboboxField::setModel(QStringList &&model)
{
    model_ = model;
    emit modelChanged();
}

void ComboboxField::setVisible(bool visible)
{
    if(qmlObject_){
        delete qmlObject_;
        qmlObject_ = nullptr;
    }

    if(!visible) return;
    if(QCoreApplication::startingUp()) return;

    QQmlEngine *engine = new QQmlEngine{this};
    QQmlComponent component(engine, QUrl(QStringLiteral("qrc:/LdProperty_combobox.qml")),
                            QQmlComponent::PreferSynchronous, this);
    QVariantMap qvMap{{"rootModel", QVariant::fromValue(this)}};
    qmlObject_ = qobject_cast<QQuickItem *>(component.createWithInitialProperties(qvMap));
    if(qmlObject_){
        qmlObject_->setParentItem(this);
        QObject::connect(qmlObject_, &QQuickItem::focusChanged,
                         this, &ComboboxField::itemFocus);
    }
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




