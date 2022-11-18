#include "network.hpp"
#include "factoryContainer.hpp"

Network::Network(QQuickItem *parent, int nr)
    : QQuickItem{parent}, nr_{nr}, containerLd_{this}
{
}

Network::Network(int nr)
    : QQuickItem{}, nr_{nr}, containerLd_{this}
{
}



void Network::changedFactory()
{
    containerLd_.setFactory(factory_);
}

