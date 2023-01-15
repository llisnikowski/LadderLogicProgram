#include "dropNetworkValidator.hpp"
#include "base.hpp"
#include "dragNetworkData.hpp"
#include <QIODevice>
#include "type.hpp"

DropNetworkValidator::DropNetworkValidator(QObject *parent)
    :Ld::DropValidator{parent}, containerLd_{}, position_{}
{

}

DropNetworkValidator::DropNetworkValidator(QObject *parent,
                                           ContainerLd *container,
                                           Position position)
    :Ld::DropValidator{parent}, containerLd_{container}, position_{position}
{
}

Qt::DropAction DropNetworkValidator::valid(const QByteArray &dragArrayData)
{
    if(!containerLd_) return Qt::DropAction::IgnoreAction;
    DragNetworkData dragNetworkData;
    if(!dragNetworkData.setData(dragArrayData)){
        return Qt::DropAction::IgnoreAction;
    }
    if(containerLd_->getId() == dragNetworkData.getId()){
        if(containerLd_->checkMoveCondition(dragNetworkData.getPosition(),
                                             position_)){

            return Qt::DropAction::CopyAction;
        }
    }
    else{
        Ld::Base *dragObj = dragNetworkData.getLdObj();
        if(!dragObj) return Qt::DropAction::IgnoreAction;
        if(dragObj->getType() >= Ld::Type::Drag){
            if(containerLd_->checkAddCondition(static_cast<Ld::Drag*>(dragObj),
                                                position_)){
                delete dragObj;
                return Qt::DropAction::MoveAction;
            }
        }
        delete dragObj;
        return Qt::DropAction::IgnoreAction;
    }

    return Qt::DropAction::IgnoreAction;
}


void DropNetworkValidator::doAction(const QByteArray &dragArrayData)
{
    if(!containerLd_) return;
    DragNetworkData dragNetworkData;
    if(!dragNetworkData.setData(dragArrayData))return;

    if(containerLd_->getId() == dragNetworkData.getId()){
        if(containerLd_->move(dragNetworkData.getPosition(),
                               position_)){

            return;
        }
    }
    else{
        Ld::Base *dragObj = dragNetworkData.getLdObj();
        if(!dragObj) return;
        if(dragObj->getType() >= Ld::Type::Drag){
            if(containerLd_->add(static_cast<Ld::Drag*>(dragObj),
                                  position_)){
                delete dragObj;
                return;
            }
        }
        delete dragObj;
    }

}



const ContainerLd *DropNetworkValidator::getContainer() const
{
    return containerLd_;
}
void DropNetworkValidator::setContainer(ContainerLd *containerLd)
{
    containerLd_ = containerLd;
}

Position DropNetworkValidator::getPosition() const
{
    return position_;
}
void DropNetworkValidator::setPosition(Position position)
{
    position_ = position;
}







