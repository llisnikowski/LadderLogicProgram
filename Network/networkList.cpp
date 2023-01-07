#include "networkList.hpp"
#include "containerLd.hpp"
#include <QDebug>
#include <functional>

NetworkList::NetworkList(QQuickItem *parent)
    :QQuickItem{parent}, networks_{}
{
    QObject::connect(this, &QQuickItem::parentChanged, this,
                     [this](QQuickItem *parent){
                         clearList();
                         if(!parent) return;
                         setWidth(parent->width());
                         connect(parent, &QQuickItem::widthChanged,
                                 this, [this,parent](){
                                     setWidth(parent->width());
                                 });
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
    connect(network, &Network::deletionTriggering, this,
            std::bind(&NetworkList::remove, this, networks_.count()-1));
    setHeight(positionY + network->height());
}

void NetworkList::remove(uint nr)
{
    if(nr >= networks_.count() - 1) return;
    networks_[nr]->deleteLater();
    networks_.removeAt(nr);
    for(int i = nr; i < networks_.count(); i++){
        Network *network = networks_[i];
        network->setNr(i);
        disconnect(network, &Network::deletionTriggering, this, nullptr);
        connect(network, &Network::deletionTriggering, this,
                std::bind(&NetworkList::remove, this, i));
    }
    updateHeight(nr);
}

void NetworkList::updateHeight(uint nr)
{
    if(nr >= networks_.count()) return;
    int y = 0;
    if(nr > 0){
        y = networks_[nr-1]->y() + networks_[nr-1]->height();
    }
    for(int i = nr; i < networks_.count(); i++){
        networks_[i]->setY(y);
        y += networks_[i]->height();
    }
    setHeight(y);
}

void NetworkList::clearList()
{
    for(auto network : networks_){
        delete network;
    }
    networks_.clear();
}

Network *NetworkList::getNetwork(int i)
{
    if(i >= networks_.count()) return nullptr;
    return networks_[i];
}

Network *NetworkList::operator[](int i)
{
    return getNetwork(i);
}

int NetworkList::count() const
{
    return networks_.count();
}



QDataStream &operator<<(QDataStream &stream, NetworkList &networkList)
{
    int networkCount = networkList.count();
    stream << networkCount;
    for(int i = 0; i < networkCount; i++){
        Network *network = networkList.networks_[i];
        stream << *network;
    }
    return stream;
}

QDataStream &operator>>(QDataStream &stream, NetworkList &networkList)
{
    networkList.clearList();
    int networkCount;
    stream >> networkCount;
    for(int i = 0; i < networkCount; i++){
        auto network = new Network{&networkList};
        network->setNr(i);
        networkList.networks_.append(network);
        QObject::connect(network, &Network::changedHeight,
                &networkList, &NetworkList::updateHeight);
        QObject::connect(network, &Network::deletionTriggering, &networkList,
                std::bind(&NetworkList::remove, &networkList, i));
        stream >> *network;
    }
    networkList.updateHeight(0);
    Network *network = networkList.networks_.last();
    QObject::connect(&network->getContainerLd(), &ContainerLd::addLdObject,
            &networkList, &NetworkList::addNewNetwork);
    return stream;
}
















