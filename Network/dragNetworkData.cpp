#include "dragNetworkData.hpp"
#include <QIODevice>
#include "base.hpp"
#include "ldFunction.hpp"

DragNetworkData::DragNetworkData(QObject *parent)
    :Ld::DragData{parent}, comp_{}, containerId_{}, position_{}
{

}

DragNetworkData::DragNetworkData(QObject *parent, QByteArray comp,
                                 int containerId, QPoint position)
    :Ld::DragData{parent}, comp_{comp}, containerId_{containerId}, position_{position}
{
}

QByteArray DragNetworkData::getData() const
{
    QByteArray itemData;
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);
    dataStream << comp_ << containerId_ << position_;
    return itemData;
}

bool DragNetworkData::setData(const QByteArray & data)
{
    QDataStream dataStream(data);
    dataStream >> comp_ ;
    dataStream >> containerId_;
    dataStream >> position_;
    if(dataStream.status() != QDataStream::Ok){
        return false;
    }
    return true;
}

Ld::Base *DragNetworkData::getLdObj() const
{
    return getLdObject(comp_);
}


QByteArray DragNetworkData::getLd() const
{
    return comp_;
}
void DragNetworkData::setLd(const Ld::Base &comp)
{
    comp_ = comp.getData();
}

int DragNetworkData::getContainerId() const
{
    return containerId_;
}
void DragNetworkData::setContainerId(int id)
{
    containerId_ = id;
}

QPoint DragNetworkData::getPosition() const
{
    return position_;
}
void DragNetworkData::setPosition(QPoint position)
{
    position_ = position;
}












