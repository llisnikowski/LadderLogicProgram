#include "network.hpp"
#include "factory.hpp"

Network::Network(QQuickItem *parent, int nr)
    : QQuickItem{parent}, nr_{nr}, containerLd_{this}
{
}

Network::Network(int nr)
    : QQuickItem{}, nr_{nr}, containerLd_{this}
{
}

void Network::setFactory(Ld::Factory *factory)
{
    this->factory_ = factory;
    containerLd_.setFactory(factory);
    qDebug() << "setFactory";
}

Ld::Factory *Network::getFactory()
{
    return factory_;
}
