#include "address.hpp"
#include <QQmlEngine>
#include <QQmlContext>
#include <QProperty>

namespace LdProperty {

Address::Address(QQuickItem *parent)
    :TextField{parent}, qmlObject{}
{
    display();
}

Address::~Address()
{
    if(qmlObject) delete qmlObject;
}

Type Address::getType() const
{
    return Type::Address;
}

void Address::display()
{
    if(QCoreApplication::startingUp()) return;
    if(qmlObject) delete qmlObject;

    QQmlEngine *engine = new QQmlEngine{this};
    qDebug() << "";
    QQmlComponent component(engine, QUrl(QStringLiteral("qrc:/LdProperty_textField.qml")),
                            QQmlComponent::PreferSynchronous, this);
    QVariantMap qvMap{{"rootModel", QVariant::fromValue(this)}};
    qmlObject = qobject_cast<QQuickItem *>(component.createWithInitialProperties(qvMap));
    if(qmlObject){
        qmlObject->setParentItem(this);
    }
}



} // namespace LdProperty


