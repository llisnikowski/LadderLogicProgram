#include "selectItem.hpp"
#include "Ld/base.hpp"
#include "drag.hpp"
#include <functional>

SelectItem::SelectItem(QObject *parent)
    : QObject{parent}, selectedItem_{}
{

}

void SelectItem::addItemToList(Ld::Base *item)
{
    QObject::connect(item, &Ld::Base::clicked,
                     std::bind(&SelectItem::setItem, this, item));
    QObject::connect(item, &QObject::destroyed,
                     std::bind(&SelectItem::removeItemFromList, this, item));

    if(auto drag = qobject_cast<Ld::Drag*>(item)){
        QObject::connect(drag, &Ld::Drag::dragged,
                         this, &SelectItem::resetItem);
    }
}

void SelectItem::removeItemFromList(Ld::Base *item)
{
    QObject::disconnect(item, nullptr, this, nullptr);
    if(item == selectedItem_){
        selectedItem_ = nullptr;
        emit changedSelectItem(nullptr);
    }

}

void SelectItem::setItem(Ld::Base *item)
{
    if(item == selectedItem_) return;
    if(selectedItem_){
        selectedItem_->setSelect(false);
    }
    selectedItem_ = item;
    emit changedSelectItem(item);
}

void SelectItem::resetItem()
{
    if(!selectedItem_) return;
    selectedItem_->setSelect(false);
    selectedItem_ = nullptr;
    emit changedSelectItem(nullptr);
}

Ld::Base *SelectItem::getSelectedItem()
{
    return selectedItem_;
}
