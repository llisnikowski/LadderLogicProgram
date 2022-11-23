#include "dropNetworkValidator.hpp"
#include "base.hpp"
#include "dragNetworkData.hpp"
#include <QIODevice>
#include "ldFunction.hpp"
#include "type.hpp"

DropNetworkValidator::DropNetworkValidator(QObject *parent)
    : Ld::DropValidator{parent}, containerLd_{}, position_{}
{

}

Qt::DropAction DropNetworkValidator::valid(const QByteArray &dragArrayData)
{
    DragNetworkData dragNetworkData;
    dragNetworkData.setData(dragArrayData);
    Ld::Base *ldObject = getLdObject(dragNetworkData.getLd());
    if(!ldObject){
        return Qt::DropAction::IgnoreAction;
    }
    if(ldObject->getType() < Ld::Type::Drag){
        return Qt::DropAction::IgnoreAction;
    }



    delete ldObject;
    return Qt::DropAction::IgnoreAction;
}



const ContainerLd *DropNetworkValidator::getContainer() const
{
    return containerLd_;
}
void DropNetworkValidator::setContainer(const ContainerLd *containerLd)
{
    containerLd_ = containerLd;
}

QPoint DropNetworkValidator::getPosition() const
{
    return position_;
}
void DropNetworkValidator::setPosition(QPoint position)
{
    position_ = position;
}







