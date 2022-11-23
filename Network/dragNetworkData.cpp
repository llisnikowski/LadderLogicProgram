#include "dragNetworkData.hpp"
#include <QIODevice>
#include "base.hpp"

DragNetworkData::DragNetworkData(QObject *parent)
    : Ld::DragData{parent}
{

}

QByteArray DragNetworkData::getData() const
{
    QByteArray itemData;
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);
    dataStream << comp_ << networkId_ << position_;
    return itemData;
}

void DragNetworkData::setData(const QByteArray & data)
{
    QDataStream dataStream(data);
    dataStream >> comp_ >> networkId_ >> position_;
}


QByteArray DragNetworkData::getLd() const
{
    return comp_;
}
void DragNetworkData::setLd(const Ld::Base &comp)
{
    comp_ = comp.getData();
}

int DragNetworkData::getNetworkId() const
{
    return networkId_;
}
void DragNetworkData::setNetworkId(int id)
{
    networkId_ = id;
}

QPoint DragNetworkData::getPosition() const
{
    return position_;
}
void DragNetworkData::setPosition(QPoint position)
{
    position_ = position;
}












