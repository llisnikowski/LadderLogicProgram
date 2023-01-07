#include "network.hpp"
#include "containerLd.hpp"
#include <QQmlEngine>
#include <functional>

Network::Network(QQuickItem *parent, int nr)
    : QQuickItem{parent}, nr_{nr}, containerLd_{this},
    label_{}
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

void Network::triggerDeletion()
{
    emit deletionTriggering();
}

void Network::createLabel()
{
    if(label_) delete label_;

    if(QCoreApplication::startingUp()) return;

    QQmlEngine *engine = new QQmlEngine;
    QQmlComponent component(engine,
                            QUrl(QStringLiteral("qrc:/NetworkLabel.qml")),
                            QQmlComponent::PreferSynchronous,this);
    QVariantMap qvMap{{"network", QVariant::fromValue(this)},
                      {"parent", QVariant::fromValue(this)}};
    QObject* qobj = component.createWithInitialProperties(qvMap);
    label_ = qobject_cast<QQuickItem *>(qobj);
    engine->setObjectOwnership(label_,QQmlEngine::JavaScriptOwnership);
    if(label_){
        label_->setParentItem(this);
    }
}



QDataStream &operator<<(QDataStream &stream, Network &network)
{
    stream << network.containerLd_;
    return stream;
}

QDataStream &operator>>(QDataStream &stream, Network &network)
{
    stream >> network.containerLd_;
    return stream;
}




