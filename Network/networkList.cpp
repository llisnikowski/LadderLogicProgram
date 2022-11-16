#include "networkList.hpp"
#include "factory.hpp"

NetworkList::NetworkList(QQuickItem *parent)
    :QQuickItem{parent}, networks_{}, factory_{}
{
}


void NetworkList::setFactory(Ld::Factory *factory)
{
    this->factory_ = factory;
    update();
    qDebug() << "setFactory";
}

Ld::Factory *NetworkList::getFactory()
{
    return factory_;
}

void NetworkList::joinToParent(QQuickItem *parent)
{
    if(!parent) return;
    setParentItem(parent);
    auto network = new Network{this};
    network->setFactory(factory_);
    networks_.append(network);

}
