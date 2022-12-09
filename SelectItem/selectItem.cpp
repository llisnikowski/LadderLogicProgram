#include "selectItem.hpp"
#include "Ld/base.hpp"
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
}

void SelectItem::removeItemFromList(Ld::Base *item)
{
    QObject::disconnect(item, &QObject::destroyed, this, nullptr);
    QObject::disconnect(item, &Ld::Base::clicked, this, nullptr);
    if(item == selectedItem_) resetItem();
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
    emit changedSelectItem(nullptr);
}

Ld::Base *SelectItem::getSelectedItem()
{
    return selectedItem_;
}
