#include "typeField.hpp"
#include <QQmlEngine>

namespace LdProperty {

TypeField::TypeField(QQuickItem *parent)
    :ComboboxField{parent}, qmlObject_{}
{
    display();
}

TypeField::~TypeField()
{
    if(qmlObject_){
        delete qmlObject_;
        qmlObject_ = nullptr;
    }
}

TypeField &TypeField::operator=(const TypeField &typeField)
{
    if(this != &typeField){
        ComboboxField::operator=(typeField);
    }
    return *this;
}

void TypeField::display()
{
    if(qmlObject_){
        delete qmlObject_;
        qmlObject_ = nullptr;
    }

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
