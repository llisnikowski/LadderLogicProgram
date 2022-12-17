#include "networkList.hpp"
#include "containerLd.hpp"

NetworkList::NetworkList(QQuickItem *parent)
    :QQuickItem{parent}, networks_{}
{
    QObject::connect(this, &QQuickItem::parentChanged, this,
                     [this](QQuickItem *parent){
                         clearList();
                         if(!parent) return;
                         addNewNetwork();
                     });
}

NetworkList::~NetworkList()
{
    clearList();
}

void NetworkList::addNewNetwork()
{
    int positionY = 0;
    if(networks_.count()){
        auto lastNetwork = networks_.last();
        disconnect(&lastNetwork->getContainerLd(), &ContainerLd::addLdObject,
                   this, &NetworkList::addNewNetwork);
        positionY = lastNetwork->y() + lastNetwork->height();
    }
    auto network = new Network{this};
    network->setNr(networks_.count());
    network->setY(positionY);
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

void NetworkList::clearList()
{
    for(auto network : networks_){
        delete network;
    }
    networks_.clear();
}

