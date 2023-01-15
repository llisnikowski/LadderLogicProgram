#include "dragNetworkData.hpp"
#include <QIODevice>
#include "base.hpp"
#include "ldFunction.hpp"
#include "containerLd.hpp"

DragNetworkData::DragNetworkData(QObject *parent)
    :Ld::DragData{parent}, comp_{}, containerLd_{}, id_{}, position_{}
{

}

DragNetworkData::DragNetworkData(QObject *parent, QByteArray comp,
                                 int id, Position position)
    :Ld::DragData{parent}, comp_{comp}, containerLd_{}, id_{id}, position_{position}
{
}

DragNetworkData::DragNetworkData(QObject *parent, QByteArray comp,
                                 ContainerLd *containerLd, Position position)
    :Ld::DragData{parent}, comp_{comp}, containerLd_{containerLd}, position_{position}
{
    if(containerLd_) id_ = containerLd_->getId();
}

void DragNetworkData::doAction(Qt::DropAction action)
{
    if(action != Qt::MoveAction) return;
    if(!containerLd_) return;
    containerLd_->remove({position_});
}

QByteArray DragNetworkData::getData() const
{
    int id = id_;
    if(containerLd_){
        id = containerLd_->getId();
    }
    QByteArray itemData;
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);
    dataStream << comp_ << id << position_;
    return itemData;
}

bool DragNetworkData::setData(const QByteArray & data)
{
    QDataStream dataStream(data);
    dataStream >> comp_ ;
    dataStream >> id_;
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

int DragNetworkData::getId() const
{
    return id_;
}
void DragNetworkData::setId(int id)
{
    id_ = id;
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
    if(containerLd_) id_ = containerLd_->getId();
}












