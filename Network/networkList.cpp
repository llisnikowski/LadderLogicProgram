#include "networkList.hpp"
#include "containerLd.hpp"
#include "factory.hpp"

NetworkList::NetworkList(QQuickItem *parent)
    :QQuickItem{parent}, networks_{}
{
}


void NetworkList::joinToParent(QQuickItem *parent)
{
    if(!parent) return;
    setParentItem(parent);
    auto network = new Network{this, 0};
    network->setFactory(factory_);
    networks_.append(network);
    connect(&network->getContainerLd(), &ContainerLd::addLdObject,
            this, &NetworkList::addNewNetwork);
    connect(network, &Network::changedHeight,
            this, &NetworkList::updateHeight);
}

void NetworkList::addNewNetwork(ContainerLd *container)
{
    auto lastNetwork = networks_.last();
    disconnect(container, &ContainerLd::addLdObject,
               this, &NetworkList::addNewNetwork);
    auto network = new Network{this};
    network->setFactory(factory_);
    network->setNr(networks_.count());
    network->setY(lastNetwork->y() + lastNetwork->height());
    networks_.append(network);
    connect(&network->getContainerLd(), &ContainerLd::addLdObject,
            this, &NetworkList::addNewNetwork);
    connect(network, &Network::changedHeight,
            this, &NetworkList::updateHeight);
}

void NetworkList::updateHeight(int nr, int height)
{
    if(nr >= networks_.count()) return;
    int y = networks_[nr]->y() + networks_[nr]->height();
    for(int i = nr + 1; i < networks_.count(); i++){
        networks_[i]->setY(y);
        y += networks_[i]->height();
    }
}

void NetworkList::changedFactory()
{
    update();
}
