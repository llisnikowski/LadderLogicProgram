#include "network.hpp"
#include "containerLd.hpp"
#include <QQmlEngine>
#include <functional>

Network::Network(QQuickItem *parent, int nr)
    : QQuickItem{parent}, nr_{nr}, containerLd_{this}
{
    if(parent){
        connect(parent, &QQuickItem::widthChanged,
                this, [this, parent](){
                    setWidth(parent->width());
                });
        setWidth(parent->width());
    }
    containerLd_.setY(40);
    connect(&containerLd_, &QQuickItem::heightChanged,
            this, &Network::updateHeight);
    updateHeight();
    createLabel();
}

Network::Network(int nr)
    : QQuickItem{}, nr_{nr}, containerLd_{this}
{
    connect(&containerLd_, &QQuickItem::heightChanged,
            this, &Network::updateHeight);
    updateHeight();
}

void Network::updateHeight()
{
    setHeight(containerLd_.height() + 64);
    emit changedHeight(nr_, this->height());
}

void Network::createLabel()
{
    if(label) delete label;

    if(QCoreApplication::startingUp()) return;

    QQmlEngine *engine = new QQmlEngine;
    QQmlComponent component(engine,
                            QUrl(QStringLiteral("qrc:/NetworkLabel.qml")),
                            QQmlComponent::PreferSynchronous,this);
    QVariantMap qvMap{{"network", QVariant::fromValue(this)},
                      {"parent", QVariant::fromValue(this)}};
    QObject* qobj = component.createWithInitialProperties(qvMap);
    label = qobject_cast<QQuickItem *>(qobj);
    engine->setObjectOwnership(label,QQmlEngine::JavaScriptOwnership);
    if(label){
        label->setParentItem(this);
    }
}

