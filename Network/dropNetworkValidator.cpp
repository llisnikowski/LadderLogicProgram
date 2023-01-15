#include "dropNetworkValidator.hpp"
#include "base.hpp"
#include "dragNetworkData.hpp"
#include <QIODevice>
#include "type.hpp"
#include <memory>

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
        std::unique_ptr<Ld::Base> dragObj{dragNetworkData.getLdObj()};
        if(!dragObj)
            return Qt::DropAction::IgnoreAction;
        if(dragObj->getType() != Ld::Type::Address)
            return Qt::DropAction::IgnoreAction;
        if(containerLd_->checkAddCondition(
                static_cast<Ld::Address*>(dragObj.get()),position_)){
            return Qt::DropAction::MoveAction;

        }
    }

    return Qt::DropAction::IgnoreAction;
}


void DropNetworkValidator::doAction(const QByteArray &dragArrayData)
{
    if(!containerLd_) return;
    DragNetworkData dragNetworkData;
    if(!dragNetworkData.setData(dragArrayData))return;

    if(containerLd_->getId() == dragNetworkData.getId()){
        containerLd_->move(dragNetworkData.getPosition(), position_);
    }
    else{
        std::unique_ptr<Ld::Base> dragObj{dragNetworkData.getLdObj()};
        if(!dragObj) return;
        if(dragObj->getType() != Ld::Type::Address) return;
        containerLd_->add(static_cast<Ld::Address*>(dragObj.get()), position_);
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







