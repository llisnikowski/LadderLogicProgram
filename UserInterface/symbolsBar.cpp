/*!
 * \file symbolsBar.cpp
 * \author Łukasz Liśnikowski
*/
#include "symbolsBar.hpp"
#include "contact.hpp"
#include "coil.hpp"
#include "dragNetworkData.hpp"
#include "dropDeleter.hpp"
#include "emptyDrop.hpp"
#include "factory.hpp"
#include <QDebug>

namespace Ld {

SymbolsBar::SymbolsBar()
{

}


void SymbolsBar::setNewParentItem(QQuickItem *parentItem)
{
    if(!parentItem) return;
    setWidth(parentItem->width());
    setHeight(parentItem->height());
    setParentItem(parentItem);

    connect(parentItem, &QQuickItem::heightChanged, this,
            [this, parentItem](){this->setHeight(parentItem->height());}
    );

    if(!factory_) return;
    factory_->create<Ld::EmptyDrop>(this, {width(), height()},
                                    [this](Ld::EmptyDrop *obj){
        connect(this, &QQuickItem::heightChanged, obj,
                [this, obj](){obj->setHeight(this->height());});
        obj->setDropValidator(new DropDeleter(obj));
    });
    factory_->create<Ld::Contact>(this, {64, 64}, [this](Ld::Contact *obj){
        obj->setDragData(new DragNetworkData(obj, obj->getData(), -1, {}));
    });
    factory_->create<Ld::Coil>(this, {64, 64}, [this](Ld::Coil *obj){
        obj->setY(64);
        obj->setDragData(new DragNetworkData(obj, obj->getData(), -1, {}));
    });
}

void SymbolsBar::changedFactory()
{
    update();
}


} // namespace Ld
