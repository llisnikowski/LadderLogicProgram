#include "networkList.hpp"
#include "factory.hpp"

NetworkList::NetworkList(QQuickItem *parent)
    :QQuickItem{parent}, networks_{}
{
}


void NetworkList::joinToParent(QQuickItem *parent)
{
    if(!parent) return;
    setParentItem(parent);
    auto network = new Network{this};
    network->setFactory(factory_);
    networks_.append(network);

}

void NetworkList::changedFactory()
{
    update();
}
