#include "dragNetworkData.hpp"
#include <QIODevice>
#include "base.hpp"
#include "ldFunction.hpp"
#include "containerLd.hpp"

DragNetworkData::DragNetworkData(QObject *parent)
    :Ld::DragData{parent}, ldData_{}, containerLd_{}, containerId_{}, position_{}
{

}

DragNetworkData::DragNetworkData(QObject *parent, QByteArray ldData,
                                 int id, Position position)
    :Ld::DragData{parent}, ldData_{ldData}, containerLd_{}, containerId_{id}, position_{position}
{
}

DragNetworkData::DragNetworkData(QObject *parent, QByteArray ldData,
                                 ContainerLd *containerLd, Position position)
    :Ld::DragData{parent}, ldData_{ldData}, containerLd_{containerLd}, containerId_{}, position_{position}
{
    if(containerLd_) containerId_ = containerLd_->getId();
}

void DragNetworkData::doAction(Qt::DropAction action)
{
    if(action != Qt::MoveAction) return;
    if(!containerLd_) return;
    containerLd_->remove({position_});
}

QByteArray DragNetworkData::getData() const
{
    int id = containerId_;
    if(containerLd_){
        id = containerLd_->getId();
    }
    QByteArray itemData;
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);
    dataStream << ldData_ << id << position_;
    return itemData;
}

bool DragNetworkData::setData(const QByteArray & data)
{
    QDataStream dataStream(data);
    dataStream >> ldData_ ;
    dataStream >> containerId_;
    dataStream >> position_;
    if(dataStream.status() != QDataStream::Ok){
        return false;
    }
    return true;
}

Ld::Base *DragNetworkData::getLdObj() const
{
    return getLdObject(ldData_);
}


QByteArray DragNetworkData::getLd() const
{
    return ldData_;
}
void DragNetworkData::setLd(const Ld::Base &comp)
{
    ldData_ = comp.getData();
}

int DragNetworkData::getId() const
{
    return containerId_;
}
void DragNetworkData::setId(int id)
{
    containerId_ = id;
}

Position DragNetworkData::getPosition() const
{
    return position_;
}
void DragNetworkData::setPosition(Position position)
{
    position_ = position;
}

void DragNetworkData::setContainer(ContainerLd *containerLd)
{
    containerLd_ = containerLd;
    if(containerLd_) containerId_ = containerLd_->getId();
}












