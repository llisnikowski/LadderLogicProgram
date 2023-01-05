#include "networkList.hpp"
#include "containerLd.hpp"
#include <QDebug>

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
    setHeight(positionY + network->height());
}

void NetworkList::updateHeight(int nr, int height)
{
    if(nr >= networks_.count()) return;
    int y = networks_[nr]->y() + networks_[nr]->height();
    for(int i = nr + 1; i < networks_.count(); i++){
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
        networkList.addNewNetwork();
        Network *network = networkList.networks_.last();
        stream >> *network;
    }
    return stream;
}
















