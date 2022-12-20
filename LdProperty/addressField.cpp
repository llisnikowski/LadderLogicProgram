#include "addressField.hpp"
#include <QQmlEngine>

namespace LdProperty {

AddressField::AddressField(QQuickItem *parent)
    :TextField{parent}, qmlObject_{}
{
    display();
}

AddressField::~AddressField()
{
    if(qmlObject_){
        delete qmlObject_;
        qmlObject_ = nullptr;
    }
}

AddressField &AddressField::operator=(const AddressField &addressField)
{
    if(this != &addressField){
        TextField::operator=(addressField);
    }
    return *this;
}

void AddressField::display()
{
    if(qmlObject_){
        delete qmlObject_;
        qmlObject_ = nullptr;
    }

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
