#include "network.hpp"
#include "containerLd.hpp"

Network::Network(QQuickItem *parent, int nr)
    : QQuickItem{parent}, nr_{nr}, containerLd_{this}
{
    connect(&containerLd_, &QQuickItem::heightChanged,
            this, &Network::updateHeight);
    updateHeight();
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
    setHeight(containerLd_.height() + 32);
    emit changedHeight(nr_, this->height());
}

